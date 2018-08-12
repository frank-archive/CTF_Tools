#pragma once
#include<string>
unsigned char ToHex(unsigned char x);
unsigned char FromHex(unsigned char x);

std::string urlencode(const std::string & str);
std::string urldecode(const std::string & str);