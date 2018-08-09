#include"BigTypes.h"
#include<climits>
#define MIN(a,b) (a<b?a:b)

BigInteger operator+(BigInteger & a, BigInteger & b) {
	int lim = MIN(a.data.size(), b.data.size());
	short carry = 0;
	for (int i = 0; i < lim; i++) {
		int temp = a.data[i] + b.data[i] + carry;
		if (temp > SHRT_MAX)temp -= SHRT_MAX, carry = 1;
		if (temp < SHRT_MIN)temp -= SHRT_MIN, carry = -1;
	}
}

BigInteger operator-(BigInteger & a, BigInteger & b) {
	
}

BigInteger::BigInteger() {

}
