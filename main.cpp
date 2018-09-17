#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

extern void RSAExamples();
extern void BigTypesExamples();
extern void TubesExamples();
extern void CipherExamples();

extern int RE0_main();
extern int HK_main();
extern int HA_main();

using namespace std;
int main() {
	cout << "dealing with \"ha\":" << endl;
	HA_main(); cout << endl;
	cout << "dealing with repeater0:" << endl;
	RE0_main(); cout << endl;
	cout << "dealing with 管理员钦定给了香港记者?:" << endl;
	HK_main();
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

	//tip:to inject some varible into a string, make good use of format string

	//there are funtions under development. update your resporitry once a while!
	
}