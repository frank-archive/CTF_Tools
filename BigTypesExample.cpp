#include"BigTypes.h"
#include<string>
#include<iostream>
using namespace std;

void BigTypesExamples() {
	BigInteger a((string)"123456789", 16);
	cout << a.toString(10) << endl;

	a = (string)"123456789";
	a = 123456789;
	a = a + a;
	a = a * 2;

	cout << a.toString() << endl;;
	cout << a.toString(16) << endl;
	cout << a.toString(2) << endl;

	a = 123456789;
	for (int i = 0; i < 10000; i++)a = a * 2;
	cout << a.toString(10) << endl;
}