#pragma once
//this part relies on my vps, therefore unreliable
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

void RSAencode(FILE *file, PUBKEY key);
void RSAencode(FILE *file, std::string key);
void RSAdecode(FILE *file, PRIVKEY key);
void RSAdecode(FILE *file, std::string key);

void RSAencode(std::string str, PUBKEY key);
void RSAencode(std::string str, std::string key);
void RSAdecode(std::string str, PRIVKEY key);
void RSAdecode(std::string str, std::string key);