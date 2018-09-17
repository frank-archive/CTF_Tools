#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Tube.h"
#include"FormatStringBuilder.h"
using namespace std;

int RE0_main() {
	FSBuilder aa; aa.read(18, type::INTEGER);
	RemoteSession a = remote("111.230.240.83", 2333);
	a.recv();
	a.sendline(aa.result());
	int aasdfasd = 2;
	while (aasdfasd--) {
		Sleep(200);
		string temp = a.recv();
		int faa = 0;
		while (!isdigit(temp[faa]))faa++;
		sscanf(temp.substr(faa).c_str(), "%d", &faa);
		a.sendline(to_string(faa));
	}
	cout << a.recv();
	return 0;
}