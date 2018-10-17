#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include"HTTPToolkit.h"
#include"Tube.h"
#include<cstdio>
using namespace std;

int main() {
	setlocale(LC_ALL, "chs");
	RemoteSession test = remote("fanyi.youdao.com", 80);
	HTTPRequest *ind = new GETRequest("fanyi.youdao.com", "/translate?&doctype=json&type=AUTO&i=car");
	ind->table["Accept-Charset"] = "ISO-8859-1";
	test.send(ind->toString());
	Sleep(1400);
	//HTTPResponse res = parseResponse(test.recvall());

	wstring res = test.wrecv();
	res = res.substr(res.find(L"\"tgt\":\"") + 7);
	res = res.substr(0, res.find(L"\"}]"));
	wcout << res;
	/*string result = res.substr(res.find("<ul class=\"dict - basic - ul\">"));
	result = result.substr(result.find("<strong>")+8);
	result = result.substr(0, result.find("</strong>"));
	cout << result;*/
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