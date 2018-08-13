#include"RSACipher.h"
#include<iostream>
#include<string>
using namespace std;

void RSAExamples() {
	PUBKEY a = parsePublicKey("MDwwDQYJKoZIhvcNAQEBBQADKwAwKAIhAL/plnUgiIhfLqI1L98+lRX2YvxNNHXdpvihYI5UtBa3AgMBAAE=");
	cout << "bits:" << a.bits << endl << "public_e:" << a.publicExponent << endl;
	cout << "modulus:" << a.modulus.toString();
	std::pair<BigInteger, BigInteger>ret = factorize(a.modulus);
	
}
int main() {
	RSAExamples();
}