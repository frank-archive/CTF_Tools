#pragma once
#include<string>
#include<map>
#include<vector>
struct HTTPRequest {//HTTP/1.1  CONSTRUCTOR
	std::map<std::string, std::string> table;
	std::string constructHeader();
	std::string &operator [](std::string key);
	virtual std::string toString() = 0;
};
class GETRequest :public HTTPRequest {
	std::string resource;
public:
	GETRequest(const std::string &host, const std::string &resource);
	std::string toString();
};
class POSTRequest :public HTTPRequest {
	std::string target, body;
public:
	POSTRequest(
		const std::string &host,
		const std::string &target,
		const std::string &content
	);
	std::string toString();
};
class PUTRequest :public HTTPRequest {
	
};


struct HTTPResponse {
	std::map<std::string, std::string>table;

	std::string http_version; 
	int code; std::string code_desc;
	std::string body;
};
HTTPResponse parseResponse(std::string res);