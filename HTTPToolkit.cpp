#include"HTTPToolkit.h"
#include"Logger.h"
#include<sstream>
using namespace std;
typedef map<string, string>::iterator m_iterator;
string HTTPRequest::constructHeader() {
	string ret;
	for (m_iterator i = table.begin(); i != table.end(); i++)
		ret += i->first + ": " + i->second + "\r\n";
	
	ret += "\r\n";
	return ret;
}

string & HTTPRequest::operator[](string key) {
	return table[key];
}

GETRequest::GETRequest(const std::string &host, const std::string &resource) {
	table["Host"] = host;
	this->resource = resource;
}

std::string GETRequest::toString() {
	if (resource == "")resource = "/";
	std::string res = "GET " + resource + " HTTP/1.1\r\n";
	res += constructHeader();
	return res;
}

POSTRequest::POSTRequest(
		const std::string &host, 
		const std::string &target, 
		const std::string &content
	) {
	table["Host"] = host;
	this->target = target;
	this->body = content;
}

string POSTRequest::toString() {
	if (target == "")target = "/";
	string res = "POST " + target + " HTTP/1.1\r\n";
	res += constructHeader(); res += body;
	return res;
}
static string trim(const string &tx) {
	int marka = 0, markb = tx.size() - 1;
	while (!isprint(tx[marka]) || isspace(tx[marka]))marka++;
	while (!isprint(tx[markb]) || isspace(tx[markb]))markb--;
	markb++;
	return tx.substr(marka, markb - marka);
}
HTTPResponse parseResponse(string res) {
	HTTPResponse ret;
	istringstream res_str(res);
	res_str >> ret.http_version >> ret.code >> ret.code_desc;
	string line; getline(res_str, line); getline(res_str, line);
	while (line.size() != 0 && line != "\r") {
		ret.table[trim(line.substr(0, line.find(':')))] =
			trim(line.substr(line.find(':') + 1));

		getline(res_str, line);
	}
	int flag = res.find("\r\n\r\n");
	if (flag != -1)
		ret.body = res.substr(flag + 4);
	return ret;
}
