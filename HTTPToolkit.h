#pragma once
#include<string>
#include<map>

class HTTPConstructor {//HTTP/1.1
	std::map<std::string, std::string>table;
	enum Method { GET, POST, PUT, DELETE };
	Method method;
public:
	HTTPConstructor();
	void setMethod(Method a);
	std::string &operator [](std::string key);
	std::string toString();
};