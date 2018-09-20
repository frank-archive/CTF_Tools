#include"Tube.h"
#include"Logger.h"
#include<iostream>
#include<string>
using namespace std;
namespace ECB_Attack {
	char visible_char[] =
		"_abcdefghijklmnopqrstuvwxyz{}=0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\\\'()*+,-./:;<>?@[\\]^`|~";

	string banner_encrypted;
	string flag_uncovered;
}

string ECB_Atack_main() {
	setTubeLogLevel(Logger::ERROR);
	for (int i = 30; i > 0; i--) {//30=14+16
	retry_this_time:;
		RemoteSession ecb_serv = remote("123.56.218.81", 9997);
		ecb_serv.recv();
		string name = "";
		for (int j = 0; j < i; j++)name += 'a';
		ecb_serv.sendline(name);
		string message = ecb_serv.recv();
		string encrypted_banner = message.substr(0, message.find("\n"));
		string constructed_banner = "hello, " + name + ", your mission's flag is: ";

		//check if connection is valid (could be useless
		ecb_serv.sendline(constructed_banner.substr(0, 16));
		Sleep(500);
		message = ecb_serv.recv();
		message = message.substr(0, message.find("\n"));
		if (encrypted_banner.find(message) == -1) {
			//cout << ("what the...");
			ecb_serv.close();
		}

		//jump to last block
		string payload =
			constructed_banner.substr
			(16 * int(constructed_banner.size() / 16))// the last block
			+ ECB_Attack::flag_uncovered;

		//CORE PROCEDURE
		bool got = false;
		for (int i = 0; i < 96; i++) {
			system("cls");
			cout << "current: " << ECB_Attack::flag_uncovered << ECB_Attack::visible_char[i] << endl;
			try {
				ecb_serv.sendline(payload + ECB_Attack::visible_char[i]);
				//Sleep(100);
			}
			catch (exception) {
				ecb_serv.close();
				goto retry_this_time;
			}
			message = ecb_serv.recv();
			message = message.substr(0, message.find("\n"));
			if (message.size() && encrypted_banner.find(message) != -1) {
				ECB_Attack::flag_uncovered += ECB_Attack::visible_char[i];
				got = true;
				break;
			}
		}
		if (!got)goto retry_this_time;
		ecb_serv.~RemoteSession();
	}

	string flag = ECB_Attack::flag_uncovered;
	return flag;
}