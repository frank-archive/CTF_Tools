#pragma once
#include<string>
#include<vector>
//压位高精，32767进制
class BigInteger {
	std::vector<short>data;
public:
	BigInteger();
	BigInteger(std::string num, int radix = 10);
	BigInteger(short num);
	BigInteger(int num);
	BigInteger(long num);
	friend BigInteger operator +(BigInteger &a, BigInteger &b);
	friend BigInteger operator -(BigInteger &a, BigInteger &b);
	friend BigInteger operator *(BigInteger &a, BigInteger &b);
	friend BigInteger operator /(BigInteger &a, BigInteger &b);
	friend BigInteger operator ^(BigInteger &a, BigInteger &b);


	std::string toString(int radix = 10);
};
class BigFloat {

};