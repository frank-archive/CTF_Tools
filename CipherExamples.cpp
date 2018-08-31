#include"CaesarCipher.h"
#include<iostream>
using namespace std;
void CipherExamples() {
	Caesar test("uwmkbn{siqamz_qa_bpm_ozmib_muxmzwz}");
	for (int i = 0; i < 26; i++) {
		string temp = test.roll(1);
		if (temp.find("moectf") != string::npos)
			cout << temp << endl;
	}
}