#pragma once
#include<string>
class Caesar {
	std::string text;
public:
	Caesar(std::string txt);
	std::string roll(int key);
	std::string operator =(std::string txt);
};