#define _CRT_SECURE_NO_WARNINGS
#include"RSACipher.h"
#include"Tube.h"
#include"Logger.h"
#include"HTTPToolkit.h"
#include<regex>
#include<vector>
using namespace std;

//MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDdP8cq736Eu69XH3KniBozD0dyrafW5D+8KcWhrEpM+NJ5wx2uWRTHTxzgHUMqfTwveBNaWM7ayQbUhatqZYDeJQGrpexp+N46C9nYV3kUmi9SFe8w3JOy6VBFw6s/zP2OGWwGMeZ5AcxIprevnwVHAwdqjYKGm9/s2zIOaOPA7QIDAQAB

/*
Public-Key: (1024 bit)
Modulus:
00:dd:3f:c7:2a:ef:7e:84:bb:af:57:1f:72:a7:88:
1a:33:0f:47:72:ad:a7:d6:e4:3f:bc:29:c5:a1:ac:
4a:4c:f8:d2:79:c3:1d:ae:59:14:c7:4f:1c:e0:1d:
43:2a:7d:3c:2f:78:13:5a:58:ce:da:c9:06:d4:85:
ab:6a:65:80:de:25:01:ab:a5:ec:69:f8:de:3a:0b:
d9:d8:57:79:14:9a:2f:52:15:ef:30:dc:93:b2:e9:
50:45:c3:ab:3f:cc:fd:8e:19:6c:06:31:e6:79:01:
cc:48:a6:b7:af:9f:05:47:03:07:6a:8d:82:86:9b:
df:ec:db:32:0e:68:e3:c0:ed
Exponent: 65537 (0x10001)
Modulus=DD3FC72AEF7E84BBAF571F72A7881A330F4772ADA7D6E43FBC29C5A1AC4A4CF8D279C31DAE5914C74F1CE01D432A7D3C2F78135A58CEDAC906D485AB6A6580DE2501ABA5EC69F8DE3A0BD9D85779149A2F5215EF30DC93B2E95045C3AB3FCCFD8E196C0631E67901CC48A6B7AF9F054703076A8D82869BDFECDB320E68E3C0ED
*/

//please erase the line breaks before calling this function
PUBKEY parsePublicKey(string pubkey) {
	string p, q;

	Logger tlog; tlog.debug("requesting PUBKEY parse\n");
	RemoteSession a = remote("service.std-frank.club", 7456);
	a.sendline(string("pub ") + pubkey);
	tlog.debug("request sent...recving...\n");
	string ret_str = a.recvall();
	PUBKEY ret;
	sscanf(ret_str.c_str(), "Public-Key: (%d bit)", &ret.bits);
	sscanf(ret_str.substr(ret_str.find("Exponent: ")).c_str(), 
		"Exponent: %d (", &ret.publicExponent);

	ret.modulus =
		BigInteger(ret_str.substr(ret_str.find("Modulus=") + 8,
			ret_str.find("---") - ret_str.find("Modulus=") - 8), 16);
	return ret;
}
#include<iostream>
pair<BigInteger, BigInteger> factorize(BigInteger a) {
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
	return std::pair<BigInteger, BigInteger>(pq[0], pq[1]);
}
