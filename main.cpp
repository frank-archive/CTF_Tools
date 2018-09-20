#include<iostream>
#include<vector>
#include<string>

extern void RSAExamples();
extern void BigTypesExamples();
extern void TubesExamples();
extern void CipherExamples();

using namespace std;

extern string RE0_main();
extern string HK_main();
extern string HA_main();
extern string ECB_Atack_main();
extern string Cirno_main();
extern string TOF_main();

int main() {
	vector<string> flags;
	string names[] = { "Cirno","ha","repeater0","HK_journalist","ECB_Attack", "True_or_False" };
	cout << "dealing with Cirno:" << endl << (flags.push_back(Cirno_main()), flags[0]) << endl;
	cout << "dealing with \"ha\":" << endl << (flags.push_back(HA_main()), flags[1]) << endl;
	cout << "dealing with repeater0:" << endl << (flags.push_back(RE0_main()),flags[2]) << endl;
	cout << "dealing with 管理员钦定给了香港记者?:" << endl<< (flags.push_back(HK_main()),flags[3]) << endl;
	cout << "dealing with ECB_Attack:" << endl << (flags.push_back(ECB_Atack_main()), flags[4]) << endl;
	cout << "dealing with True or False:" << endl << (flags.push_back(TOF_main()), flags[5]) << endl;
	
	for (int i = 0; i < flags.size(); i++)
		cout << names[i] << ":" << flags[i] << endl;

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