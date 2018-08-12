#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"FormatStringBuilder.h"
#include"Tube.h"
using namespace std;

int main() {
	//happy hacking!
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

	//TODO list:
	//1/  

	//this is an example:
	//FSBuilder aa; aa.read(18, type::LNG);
	//RemoteSession a = remote("111.230.240.83", 2333);
	//a.recv();
	//a.sendline(aa.result());
	//int aasdfasd = 2;
	//while (aasdfasd--) {
	//	Sleep(200);
	//	string temp = a.recv();
	//	int faa = 0;
	//	while (!isdigit(temp[faa]))faa++;
	//	sscanf(temp.substr(faa).c_str(), "%d", &faa);
	//	a.sendline(to_string(faa));
	//}
	//cout << a.recv();

	//this is another example:
	//string afds;
	//string a = "";
	//for (int j = 0; j < 76; j++)a += '\0';
	//a += char(134); a += char(7);//00000111(7) 10000110(134)
	//RemoteSession ses = remote("123.56.218.81", 9999);
	//ses.recv();
	//ses.sendline(a);
	//Sleep(200);
	//afds = ses.recv();
	//cout << afds;
}