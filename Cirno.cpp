#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<stack>
#include<algorithm>
#pragma comment(lib,"Ws2_32.lib ")
using namespace std;
stack<char>operators;
stack<int> operands;

bool process() {
	char operation = operators.top();
	operators.pop();
	int a = operands.top(); operands.pop();
	int b = operands.top(); operands.pop();
	switch (operation) {
	case '+':
		operands.push(a + b);
		break;
	case '-':
		operands.push(b - a);
		break;
	case '*':
		operands.push(a*b);
		break;
	case '/':
		if (a == 0) return false;
		if (b%a)return false;
		operands.push(b / a);
	}
	return true;
}
int cal(string expr) {
	while (!operators.empty())operators.pop();
	while (!operands.empty())operands.pop();
	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == ' ')continue;
		if (expr[i] == '+' || expr[i] == '-') {
			char temp;
			while (!operators.empty() &&
				((temp = operators.top()) == '+' || temp == '-' || temp == '*' || temp == '/'))
				if (process() == false)return -1;
			operators.push(expr[i]);
		}
		else if (expr[i] == '*' || expr[i] == '/') {
			char temp;
			while (!operators.empty() &&
				((temp = operators.top()) == '*' || (temp = operators.top()) == '/'))
				if (process() == false)return -1;
			operators.push(expr[i]);
		}
		else {
			int num = 0;
			while (i < expr.length() && expr[i] >= '0'&&expr[i] <= '9') {
				num *= 10;
				num += expr[i] - '0';
				i++;
			}
			i--;
			operands.push(num);
		}
	}
	while (operands.size() > 1)if (process() == false)return -1;
	return operands.top();
}
char to_symbol(int i) {
	switch (i) {
	case 0:return '+';
	case 1:return '-';
	case 2:return '*';
	case 3:return '/';
	}
	return 0;
}

SOCKET server;
bool read(string &i) {
	char buffer[2048];
	memset(buffer, 0, sizeof buffer);
	if (recv(server, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
		closesocket(server);
		WSACleanup();
		cout << "read error";
		exit(0);
	}
	i = buffer;
	if (i.size())return true;
	return false;
}
void put(string &m) {
	cout << "sent:" << m << endl;
	if (send(server, m.c_str(), m.size(), 0) == SOCKET_ERROR) {
		closesocket(server);
		WSACleanup();
		cout << "put error";
		exit(0);
	}
}
string Cirno_main() {
	string flag;
	WSAData wd;
	/*assert*/(WSAStartup(MAKEWORD(2, 2), &wd));
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(9998);
	addrServ.sin_addr.S_un.S_addr = inet_addr("123.56.218.81");
	int ret = connect(server, (SOCKADDR*)&addrServ, sizeof(SOCKADDR));//开始连接
	if (SOCKET_ERROR == ret) {
		printf("socket connect failed\n");
		WSACleanup();
		closesocket(server);
		cout << "this time failed";
		return Cirno_main();
	}

	string in;
	while (read(in)) {

		if (in.find("moectf") != -1) {
			system("cls");
			flag = in;
			break;
		}

		cout << in;
		int fl = in.size(); while (in[fl] != ':')fl--;
		in = in.substr(fl, in.size() - fl);

		int arr[4];
		sscanf(in.c_str(), ":%d, %d, %d, %d", &arr[0], &arr[1], &arr[2], &arr[3]);

		while (prev_permutation(arr, arr + 4));
		next_permutation(arr, arr + 4);

		while (next_permutation(arr, arr + 4)) {
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					for (int k = 0; k < 4; k++) {
						string exp = to_string(arr[0]) + to_symbol(i) +
							to_string(arr[1]) + to_symbol(j) +
							to_string(arr[2]) + to_symbol(k) +
							to_string(arr[3]);
						//cout << exp;
						if (cal(exp) == 9) {
							put(exp);
							goto end;
						}
					}
		}
	end:;
	}
	closesocket(server);
	WSACleanup();
	return flag;
}