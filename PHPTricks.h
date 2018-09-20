#pragma once
#include<string>

struct FileInclude {
	std::string src, target;
	bool base64_encode;
	FileInclude(std::string s, std::string t, bool b);
	std::string toString();
};