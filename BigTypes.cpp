#include"BigTypes.h"
#include<climits>
#include<stack>
#include<utility>
#include<sstream>

template<typename type>
void swap(type &a, type &b) {
	a = a ^ b; b = a ^ b; a = a ^ b;
}

void reverse(std::string &a) {
	for (int i = 0; i < a.size() / 2; i++)
		swap(a[i], a[a.size() - 1 - i]);
}
inline short performCarry(long long num, short &carry, short radix) {
	carry = num / radix;
	num %= radix;
	return num;
}
BigInteger operator+(BigInteger & a, BigInteger & b) {
	if (a.ST_BASE != b.ST_BASE)b.toggleBase(a.ST_BASE);
	BigInteger ret;
	BigInteger *less = &a, *more = &b;
	if (a.data.size() > b.data.size())less = &b, more = &a;
	short carry = 0;
	for (int i = 0; i < less->data.size(); i++) {
		long temp = less->data[i] + more->data[i] + carry;
		temp = performCarry(temp, carry, a.ST_BASE);
		ret.data.push_back(temp);
	}
	for (int i = less->data.size(); i < more->data.size(); i++) {
		long temp = more->data[i] + carry;
		temp = performCarry(temp, carry, a.ST_BASE);
		ret.data.push_back(temp);
	}
	if (carry)ret.data.push_back(carry);
	ret.tidy();
	return ret;
}

BigInteger operator-(BigInteger & a, BigInteger & b) {
	if (a.ST_BASE != b.ST_BASE)b.toggleBase(a.ST_BASE);
	BigInteger ret;
	BigInteger *less = &a, *more = &b;
	if (a.data.size() > b.data.size())less = &b, more = &a;
	short carry = 0;
	for (int i = 0; i < less->data.size(); i++) {
		long temp = less->data[i] - more->data[i] + carry;
		temp = performCarry(temp, carry, a.ST_BASE);
		ret.data.push_back(temp);
	}
	for (int i = less->data.size(); i < more->data.size(); i++) {
		long temp = more->data[i] + carry;
		temp = performCarry(temp, carry, a.ST_BASE);
		ret.data.push_back(temp);
	}
	if (carry)ret.data.push_back(carry);
	ret.tidy();
	return ret;
}

BigInteger operator*(BigInteger & a, long b) {
	BigInteger ret;
	short carry = 0;
	for (int i = 0; i < a.data.size(); i++) {
		long long temp = b * a.data[i] + carry;
		temp = performCarry(temp, carry, a.ST_BASE);
		ret.data.push_back(temp);
	}
	if (carry)ret.data.push_back(carry);
	ret.tidy();
	return ret;
}

std::pair<BigInteger, long>div_mod(BigInteger &a, long b) {
	long long temp = 0; BigInteger ret;
	ret.ST_BASE = a.ST_BASE;
	std::stack<short>rts;
	for (int i = a.data.size() - 1; i >= 0; i--) {
		temp *= a.ST_BASE; temp += a.data[i];
		rts.push(temp / b);
		temp %= b;
	}
	while (!rts.empty()) {
		ret.data.push_back(rts.top());
		rts.pop();
	}
	ret.tidy();
	return std::pair<BigInteger, long>(ret, temp);
}
BigInteger operator/(BigInteger & a, long b) {
	return div_mod(a, b).first;
}
long operator%(BigInteger & a, long b) {
	return div_mod(a, b).second;
}

//ÄæÐòreversed
std::vector<short> BigInteger::toBase(short base) {
	BigInteger temp = *this; std::vector<short>ret;
	std::pair<BigInteger, long>rts;
	while (temp.data.size()) {
		rts = div_mod(temp, base);
		ret.push_back(rts.second);
		temp = rts.first;
	}
	return ret;
}

void BigInteger::fromBase(std::vector<short>& num/*reversed*/, short ORIG_BASE) {
	//.....is there any method that is not as brutal as THIS
	ST_BASE = SHRT_MAX;
	BigInteger temp; temp.data = num;
	temp.ST_BASE = ORIG_BASE;
	data = temp.toBase(ST_BASE);
}

void BigInteger::toggleBase(short base) {
	data = toBase(base);
}

BigInteger::BigInteger() {
	ST_BASE = SHRT_MAX;
}

BigInteger::BigInteger(std::string num, int radix) {
	ST_BASE = SHRT_MAX;
	std::vector<short>temp;
	reverse(num);
	for (int i = 0; i < num.size(); i++) {
		if (num[i] >= '0'&&num[i] <= '9')
			temp.push_back(num[i] - '0');
		else if (num[i] >= 'A'&&num[i] <= 'Z')
			temp.push_back(num[i] - 'A' + 10);
		else if (num[i] >= 'a'&&num[i] <= 'z')
			temp.push_back(num[i] - 'a' + 10);
	}
	fromBase(temp, radix);
}

BigInteger::BigInteger(long num) {
	ST_BASE = SHRT_MAX;
	while (num != 0) {
		this->data.push_back(num%ST_BASE);
		num /= ST_BASE;
	}
}

BigInteger::~BigInteger() {
	data.clear();
}

void BigInteger::tidy() {
	while (data.size() && data[data.size() - 1] == 0)
		data.pop_back();

	if (data.size()>1) {
		int symbol = data[data.size() - 1] >= 0 ? 1 : -1;
		for (int i = data.size() - 2; i >= 0; i--) {
			while (data[i] * symbol < 0) {
				data[i + 1] --;
				data[i] += symbol * ST_BASE;
			}
		}
	}
}
std::string BigInteger::toString(short radix) {
	if (data.size() == 0)return "0";
	std::vector<short>temp = toBase(radix);
	std::string ret; int symbol = temp[temp.size() - 1] < 0 ? -1 : 1;
	if (symbol == -1)ret += "-";
	for (int i = temp.size() - 1; i >= 0; i--) {
		if (symbol*temp[i] < 10)ret += (symbol*temp[i] + '0');
		else if (symbol*temp[i] < 36)ret += (symbol*temp[i] + 'A' - 10);
		else {
			ret = "radix limit exceeded";
			return ret;
		}
	}
	return ret;
}

int BigInteger::toInt() {
	int ret;
	std::istringstream sin(toString());
	sin >> ret;
	return ret;
}
