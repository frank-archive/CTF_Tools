#include "BaseEncoding.h"
#include"algo_ext.h"
using namespace std;
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
int base64_index(const char &a) {
	if (a >= 'A'&&a <= 'Z')return a - 'A';
	if (a >= 'a'&&a <= 'z')return a - 'a' + 26;
	if (a >= '0'&&a <= '9')return a - '0' + 52;
	if (a == '+')return 63; if (a == '/')return 64;
	if (a == '=')return 0;
	return -1;
}
static const string base32_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"234567";
int base32_index(const char &a) {
	if (a >= 'A'&&a <= 'Z')return a - 'A';
	if (a >= '2'&&a <= '7')return a - '2' + 26;
	if (a == '=')return 0;
	return -1;
}
static const string base16_chars =
"0123456789"
"ABCDEF";
int base16_index(const char &a) {
	if (a >= '0'&&a <= '9')return a - '0';
	if (a >= 'A'&&a <= 'F')return a - 'A' + 10;
	return -1;
}

static string enmap(string &arr, const int targ_bit) {
	int fillbit = 0;
	string ret, unitbuf;
	int unit_bits = lcm(targ_bit, 8);
	int orig_unit = unit_bits / 8;
	int mapd_unit = unit_bits / targ_bit;
	while (arr.size() % orig_unit)arr += '\0', fillbit += 8;
	for (int i = 0; i < arr.size(); i += orig_unit) {
		int step = 0;
		unitbuf = ""; unitbuf.resize(mapd_unit);
		for (int j = 0; j < mapd_unit; j++) {
			for (int k = 0; k < targ_bit; k++, step++)
				unitbuf[j] |=
				((arr[i + step / 8] >> (7 - step % 8)) & 1) << (targ_bit - k - 1);
		}
		ret += unitbuf;
	}
	while (fillbit > targ_bit)
		ret.pop_back(), fillbit -= targ_bit;
	return ret;
}
static string demap(string &arr, const int orig_bit) {
	string ret, unitbuf;
	int unit_bits = lcm(orig_bit, 8);
	int orig_unit = unit_bits / 8;
	int mapd_unit = unit_bits / orig_bit;
	for (int i = 0; i < arr.size(); i += mapd_unit) {
		int step = 0;
		unitbuf = ""; unitbuf.resize(orig_unit);
		for (int j = 0; j < orig_unit; j++) {
			for (int k = 0; k < 8; k++, step++)
				unitbuf[j] |=
				((arr[i + step / orig_bit] >> (orig_bit - 1 - step % orig_bit) & 1) << (7 - k));
		}
		ret += unitbuf;
	}
	while (ret[ret.size() - 1] == 0)
		ret.pop_back();
	return ret;
}


string base64::b64encode(string txt) {
	txt = enmap(txt, 6);
	for (int i = 0; i < txt.size(); i++)
		txt[i] = base64_chars[txt[i]];
	while (txt.size() % 4)txt += '=';
	return txt;
}
string base64::b64decode(string enc) {
	for (int i = 0; i < enc.size(); i++) {
		enc[i] = base64_index(enc[i]);
		if (enc[i] == -1)
			return "not base64 encoded string";
	}
	enc = demap(enc, 6);
	return enc;
}


string base64::b32encode(string txt) {
	txt = enmap(txt, 5);
	for (int i = 0; i < txt.size(); i++)
		txt[i] = base32_chars[txt[i]];
	while (txt.size() % 8)txt += '=';
	return txt;
}
string base64::b32decode(string enc) {
	for (int i = 0; i < enc.size(); i++) {
		enc[i] = base32_index(enc[i]);
		if (enc[i] == -1)
			return "not base64 encoded string";
	}
	enc = demap(enc, 5);
	return enc;
}


string base64::b16encode(string txt) {
	txt = enmap(txt, 4);
	for (int i = 0; i < txt.size(); i++)
		txt = base16_chars[txt[i]];
	// no need to append =
	return txt;
}
string base64::b16decode(string enc) {
	for (int i = 0; i < enc.size(); i++) {
		enc[i] = base16_index(enc[i]);
		if (enc[i] == -1)
			return "not base64 encoded string";
	}
	enc = demap(enc, 4);
	return enc;
}