#include"BigTypes.h"
#include<climits>
#define STORAGE_BASE SHRT_MAX

inline short performCarry(long long num, short &carry) {
	carry = num / STORAGE_BASE;
	num %= STORAGE_BASE;
	return num;
}

BigInteger operator+(BigInteger & a, BigInteger & b) {
	BigInteger ret;
	BigInteger *less = &a, *more = &b;
	if (a.data.size() > b.data.size())less = &b, more = &a;
	short carry = 0;
	for (int i = 0; i < less->data.size(); i++) {
		long temp = less->data[i] + more->data[i] + carry;
		temp = performCarry(temp, carry);
		ret.data.push_back(temp);
	}
	for (int i = less->data.size(); i < more->data.size(); i++) {
		long temp = more->data[i] + carry;
		temp = performCarry(temp, carry);
		ret.data.push_back(temp);
	}
	if (carry)ret.data.push_back(carry);
	return ret;
}

BigInteger operator-(BigInteger & a, BigInteger & b) {
	BigInteger ret;
	BigInteger *less = &a, *more = &b;
	if (a.data.size() > b.data.size())less = &b, more = &a;
	short carry = 0;
	for (int i = 0; i < less->data.size(); i++) {
		long temp = less->data[i] - more->data[i] + carry;
		temp = performCarry(temp, carry);
		ret.data.push_back(temp);
	}
	for (int i = less->data.size(); i < more->data.size(); i++) {
		long temp = more->data[i] + carry;
		temp = performCarry(temp, carry);
		ret.data.push_back(temp);
	}
	if (carry)ret.data.push_back(carry);
	return ret;
}

BigInteger operator*(BigInteger & a, long b) {
	BigInteger ret;
	short carry = 0;
	for (int i = 0; i < a.data.size(); i++) {
		long long temp = b * a.data[i] + carry;
		temp = performCarry(temp, carry);
		ret.data.push_back(temp);
	}
	if (carry)ret.data.push_back(carry);
	return ret;
}

BigInteger::BigInteger() {

}

BigInteger::BigInteger(int num) {
	std::vector<short>temp;
	while (num != 0) {
		temp.push_back(num%STORAGE_BASE);
		num /= STORAGE_BASE;
	}
	for (int i = temp.size() - 1; i >= 0; i--)
		this->data.push_back(temp[i]);
}