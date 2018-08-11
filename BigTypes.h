#pragma once
#include<string>
#include<vector>
//压位高精，32767进制
namespace BigTypes {
	class BigInteger {
		short ST_BASE;
		std::vector<short>data;
		std::vector<short>toBase(short base);
		void              fromBase(std::vector<short>&num, short ORIG_BASE);
		void              toggleBase(short base);
	public:
		BigInteger();
		BigInteger(std::string num, int radix = 10);
		BigInteger(long num);
		~BigInteger();
		friend BigInteger operator +(BigInteger &a, BigInteger &b);
		friend BigInteger operator -(BigInteger &a, BigInteger &b);
		friend BigInteger operator *(BigInteger &a, BigInteger &b);
		friend BigInteger operator *(BigInteger &a, long b);
		friend BigInteger operator /(BigInteger &a, BigInteger &b);
		friend std::pair<BigInteger, long>div_mod(BigInteger &a, long b);
		friend BigInteger operator /(BigInteger &a, long b);
		friend long       operator %(BigInteger &a, long b);
		friend BigInteger operator ^(BigInteger &a, BigInteger &b);

		void tidy();
		std::string toString(short radix = 10);
	};
	class BigFloat {

	};
}