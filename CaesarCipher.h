#pragma once
#include<string>
class Caesar {
	std::string text;
	std::string roll(int key);
public:
	Caesar(std::string txt);
	std::string operator ++();
	std::string operator --();
	std::string operator +=(int bias);
	std::string operator -=(int bias);
	std::string operator =(std::string txt);
};