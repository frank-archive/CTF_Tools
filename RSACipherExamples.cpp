#include"RSACipher.h"
#include<iostream>
#include<string>
using namespace std;

void RSAExamples() {
	PUBKEY a = parsePublicKey("MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDdP8cq736Eu69XH3KniBozD0dyrafW5D+8KcWhrEpM+NJ5wx2uWRTHTxzgHUMqfTwveBNaWM7ayQbUhatqZYDeJQGrpexp+N46C9nYV3kUmi9SFe8w3JOy6VBFw6s/zP2OGWwGMeZ5AcxIprevnwVHAwdqjYKGm9/s2zIOaOPA7QIDAQAB");
	cout << a.bits << endl << a.publicExponent << endl;
	cout << a.modulus.toString();
}