#pragma once
#include<string>
#include<vector>
//压位高精，32767进制
class BigInteger {
	std::vector<short>data;
	std::vector<short>toBase(short STORAGE_BASE);
public:
	BigInteger();
	BigInteger(std::string num, int radix = 10);
	BigInteger(short num);
	BigInteger(int num);
	BigInteger(long num);
	friend BigInteger operator +(BigInteger &a, BigInteger &b);
	friend BigInteger operator -(BigInteger &a, BigInteger &b);
	friend BigInteger operator *(BigInteger &a, BigInteger &b);
	friend BigInteger operator *(BigInteger &a, long b);
	friend BigInteger operator /(BigInteger &a, BigInteger &b);
	friend BigInteger operator ^(BigInteger &a, BigInteger &b);


	std::string toString(int radix = 10);
};
class BigFloat {

};