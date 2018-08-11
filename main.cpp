#include<iostream>
#include<climits>
#include"BigTypes.h"
#include"Tube.h"
#include"RSATools.h"
using namespace std;
using namespace pwn;
void BigTypesExamples() {
	BigInteger a((string)"123456789", 16);
	cout << a.toString(10) << endl;

	a = (string)"123456789";
	a = 123456789;
	a = a + a;
	a = a * 2;

	cout << a.toString() << endl;;
	cout << a.toString(16) << endl;
	cout << a.toString(2) << endl;

	a = 123456789;
	for (int i = 0; i < 10000; i++)a = a * 2;
	cout << a.toString(10) << endl;
}
void TubesExamples() {
	RemoteSession a = remote("service.std-frank.club", 7456);
	a.send("asdf\n");
	cout << a.recv();
}
void RSAExamples() {
	PUBKEY a = parsePublicKey("MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDdP8cq736Eu69XH3KniBozD0dyrafW5D+8KcWhrEpM+NJ5wx2uWRTHTxzgHUMqfTwveBNaWM7ayQbUhatqZYDeJQGrpexp+N46C9nYV3kUmi9SFe8w3JOy6VBFw6s/zP2OGWwGMeZ5AcxIprevnwVHAwdqjYKGm9/s2zIOaOPA7QIDAQAB");
	cout << a.bits << endl << a.publicExponent << endl;
	cout << a.modulus.toString();
}
int main() {
	RSAExamples();
}