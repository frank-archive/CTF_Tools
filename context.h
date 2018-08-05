#pragma once
#include<string>
struct Context {
	std::string arch;
	int bits;
	char endian;//(b)ig,(l)ittle
	int log_level;
	void clear();//set to default
};