#pragma once
//this part relies on my vps, therefore unreliable
#include<string>
#include<utility>
#include"BigTypes.h"
struct PRIVKEY {
	//bool version;//don't (want to) support multi modulus
	short bits;
	BigInteger modulus;				//n
	BigInteger publicExponent;		//e
	BigInteger privateExponent;		//d
	BigInteger prime1;				//p
	BigInteger prime2;				//q
	BigInteger exponent1;			//d mod (p-1)
	BigInteger exponent2;			//d mod (q-1)
	BigInteger coefficent;			//(inverse of q) mod p
};
struct PUBKEY {
	short bits;
	BigInteger modulus;
	BigInteger publicExponent;
};
PUBKEY parsePublicKey(std::string pubkey);
PRIVKEY parsePrivateKey(std::string privkey);

std::pair<BigInteger,BigInteger> factorize(BigInteger a);

void RSAencode(FILE *file, PUBKEY key);
void RSAencode(FILE *file, std::string key);
void RSAdecode(FILE *file, PRIVKEY key);
void RSAdecode(FILE *file, std::string key);

void RSAencode(std::string str, PUBKEY key);
void RSAencode(std::string str, std::string key);
void RSAdecode(std::string str, PRIVKEY key);
void RSAdecode(std::string str, std::string key);