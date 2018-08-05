#include<iostream>
#include"Tube.h"
using namespace std;
using namespace pwn;
int main() {
	RemoteSession a = remote("123.56.218.81", 9999);
	Sleep(200);
	cout<<a.recieve();
}