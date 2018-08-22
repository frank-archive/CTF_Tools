#define _CRT_SECURE_NO_WARNINGS
#include"RSACipher.h"
#include"Tube.h"
#include"Logger.h"
#include"HTTPToolkit.h"
#include<regex>
#include<vector>
#include<unordered_map>
using namespace std;

//pub MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDdP8cq736Eu69XH3KniBozD0dyrafW5D+8KcWhrEpM+NJ5wx2uWRTHTxzgHUMqfTwveBNaWM7ayQbUhatqZYDeJQGrpexp+N46C9nYV3kUmi9SFe8w3JOy6VBFw6s/zP2OGWwGMeZ5AcxIprevnwVHAwdqjYKGm9/s2zIOaOPA7QIDAQAB


static BigInteger convertOpensslNum(string num) {
	while (!isalnum(num[0]))num = num.substr(1);
	string build; int i = 0; bool isHex = false;
	while (num[i] == '0' || num[i] == ':')i++;
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == ':')isHex = true;
		else if (num[i] == ' ' || num[i] == '\n')
			continue;
		else if (num[i] == '(')break;
		else build += num[i];
	}
	while (build[0] == '0')build = build.substr(1);
	if (isHex)return BigInteger(build, 16);
	else return BigInteger(build, 10);
}
unordered_map<string, BigInteger> parseObj(string str) {
	unordered_map<string, BigInteger>obj_map;
	smatch result; pair<string, BigInteger>obj;
	regex_search(str, result, regex("(?:\\n)\\w+"));
	string bits_source = result.prefix().str(); int bits_ext;
	bits_source = bits_source.substr(bits_source.find("("));
	sscanf(bits_source.c_str(), "(%dbit)", &bits_ext);
	obj_map["bits"] = bits_ext;
	str = result[0].str() + result.suffix().str();
	regex_search(str, result, regex("(?:\\n)\\w+"));
	obj.first = result[0].str().substr(1);
	str = result.suffix();
	while (regex_search(str, result, regex("(?:\\n)\\w+"))) {
		obj.second = convertOpensslNum(result.prefix().str().substr(1));
		obj_map[obj.first] = obj.second;
		obj.first = result[0].str().substr(1);
		str = result.suffix();
	}
	obj.second = convertOpensslNum(str);
	obj_map[obj.first] = obj.second;
	return obj_map;
}
#include<iostream>
//please erase the line breaks before calling this function
PUBKEY parsePublicKey(string pubkey) {
	Logger tlog; tlog.debug("requesting PUBKEY parse\n");
	RemoteSession a = remote("service.std-frank.club", 7456);
	a.sendline(string("pub ") + pubkey);
	tlog.debug("request sent...recving...\n");
	string ret_str = a.recvall();
	if (ret_str.find("unable") != -1)return PUBKEY();

	PUBKEY ret;
	unordered_map<string, BigInteger>obj_map = parseObj(ret_str);
	if (obj_map.find("Modulus") == obj_map.end() ||
		obj_map.find("bits") == obj_map.end())
		return PUBKEY();
	ret.bits = obj_map["bits"].toInt();
	ret.modulus = obj_map["Modulus"];
	ret.publicExponent = obj_map["Exponent"];
	return ret;
}

//please erase the line breaks before calling this function
PRIVKEY parsePrivateKey(std::string privkey) {
	Logger tlog; tlog.debug("requesting PIRVKEY parse\n");
	RemoteSession a = remote("service.std-frank.club", 7456);
	a.sendline(string("priv ") + privkey);
	tlog.debug("request sent...recving...\n");
	string ret_str = a.recvall();
	if (ret_str.find("unable") != -1)return PRIVKEY();

	PRIVKEY ret;
	unordered_map<string, BigInteger>obj_map = parseObj(ret_str);
	if (obj_map.find("modulus") == obj_map.end() ||
		obj_map.find("bits") == obj_map.end())
		return PRIVKEY();
	ret.bits = obj_map["bits"].toInt();
	ret.modulus = obj_map["modulus"];
	ret.publicExponent = obj_map["publicExponent"];
	ret.privateExponent = obj_map["privateExponent"];
	ret.prime1 = obj_map["prime1"];
	ret.prime2 = obj_map["prime2"];
	ret.exponent1 = obj_map["exponent1"];
	ret.exponent2 = obj_map["exponent2"];
	ret.coefficent = obj_map["coefficent"];
	return ret;
}
pair<BigInteger, BigInteger> factorize(BigInteger a) {
	Logger tlog; tlog.debug("requesting n factorization\n");
	string pq[2];
	string url = "www.factordb.com";
	RemoteSession factordb = remote(url, 80);
	while (factordb.isClosed())factordb = remote(url, 80);
	HTTPRequest *req = new GETRequest("factordb.com", "/index.php?query=" + a.toString());
	(*req)["Connection"] = "keep-alive";
	factordb.send(req->toString());
	string meta = factordb.recv();
	//factordb.close();
	HTTPResponse res = parseResponse(meta);
	meta = res.body;

	smatch result; vector<string>num;
	while (regex_search(meta, result, regex("index\\.php\\?id\\=([0-9]+)"))) {
		num.push_back(result[1].str());
		meta = result.suffix().str();
	}
	for (int i = 1; i <= 2; i++) {
		//RemoteSession factordb = remote(url, 80);
		//while (factordb.isClosed())factordb = remote(url, 80);
		HTTPRequest *req = new GETRequest("factordb.com", "/index.php?id=" + num[i]);
		(*req)["Connection"] = "keep-alive";
		factordb.send(req->toString());
		meta = factordb.recv();
		HTTPResponse res = parseResponse(meta);
		meta = res.body;
		regex_search(meta, result, regex("value=\\\"([0-9]+)\\\""));
		pq[i - 1] = result[1].str();
		//factordb.close();
	}
	if (pq[0] == pq[1])return pair<BigInteger, BigInteger>(0, 0);
	tlog.debug("success\n");
	return std::pair<BigInteger, BigInteger>(pq[0], pq[1]);
}
