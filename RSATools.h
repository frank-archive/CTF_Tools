#pragma once
#include<string>
struct PRIVKEY {
	//bool version;//don't (want to) support multi modulus
	short bits;
	std::string modulus;
	std::string publicExponent;
};
struct PUBKEY {
	short bits;
	
};
PUBKEY parsePublicKey(std::string pubkey);
PRIVKEY parsePrivateKey(std::string privkey);
