#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<regex>

extern void RSAExamples();
extern void BigTypesExamples();
extern void TubesExamples();

using namespace std;
int main() {
	//happy hacking!
	//if u want to check on examples, call the extern funcs
	//please open this project with Visual Studio
	//    (latest version) for (maybe) a fine experience
	//currently supported functions:
	//1/  remote connection to a host, equivalent to the
	//    Tubes module in the pwntools library
	//2/  Big Integer Calculation
	//3/  Serveral Cipers
	//4/  Serveral Encodings
	//5/  Logger support, keep yourself informed on which
	//    step your kit is working on
	//6/  RSA Public Key Parse AND <N factorization>!
	//    with factordb(more in examples)

	//there are funtions under development. update your resporitry once a while!
	RSAExamples();
}