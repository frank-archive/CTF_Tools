#pragma once
#include<string>
#include"BigTypes.h"
struct PRIVKEY {
	//bool version;//don't (want to) support multi modulus
	short bits;
	BigInteger modulus;
	unsigned long publicExponent;
	unsigned long privateExponent;
};
struct PUBKEY {
	short bits;
	BigInteger modulus;
	unsigned long publicExponent;
};
PUBKEY parsePublicKey(std::string pubkey);
PRIVKEY parsePrivateKey(std::string privkey);
