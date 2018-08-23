#include "BaseEncode.h"
#include<bitset>
#include"algo_ext.h"
using namespace std;
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
static const string base32_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"234567";
static const string base16_chars =
"0123456789"
"ABCDEF";

static string map(string &arr, const int targ_bit) {
	int fillbit = 0;
	string ret, unitbuf; bitset<50>buf;
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
static void unmap(char *arr, int orig_bit);
string base64::b64encode(string txt) {
	string ret; int fill;
	string s=map(txt, 6);
	for (int i = 0; i < s.size(); i++)
		ret += base64_chars[s[i]];
	while (ret.size() % 4)ret += '=';
	return ret;
}
string base64::b32encode(string txt) {
	string ret;
	txt = map(txt, 5);
	for (int i = 0; i < txt.size(); i++)
		ret += base32_chars[txt[i]];
	while (ret.size() % 8)ret += '=';
	return ret;
}
string base64::b16encode(string txt) {
	string ret;
	txt = map(txt, 4);
	for (int i = 0; i < txt.size(); i++)
		ret += base16_chars[txt[i]];
	// no need to append =
	return ret;
}
//string base64::b64decode(string txt) {
//	int in_len = txt.size();
//	int i = 0, in_ = 0; unsigned char loop_trans[4], loop_orig[3]; string ret;
//	while (in_len-- && (txt[in_] != '=') && is_base64(txt[in_])) {
//		loop_trans[i++]
//			= txt[in_++]; if (i == 4) {
//			for (i = 0; i < 4; i++)
//				loop_trans[i] = base64_chars.find(loop_trans[i]); 
//			loop_orig[0] = (loop_trans[0] << 2) + ((loop_trans[1] & 0x30) >> 4); 
//			loop_orig[1] = ((loop_trans[1] & 0xf) << 4) + ((loop_trans[2] & 0x3c) >> 2);
//			loop_orig[2] = ((loop_trans[2] & 0x3) << 6) + loop_trans[3]; 
//			for (i = 0; i < 3; i++)
//				ret += loop_orig[i]; i = 0;
//		}
//	}if (i) {
//		for (int j = i; j < 4; j++)loop_trans[j] = 0;
//		for (int j = 0; j < 4; j++)loop_trans[j] = base64_chars.find(loop_trans[j]);
//		loop_orig[0] = (loop_trans[0] << 2) + ((loop_trans[1] & 0x30) >> 4); 
//		loop_orig[1] = ((loop_trans[1] & 0xf) << 4) + ((loop_trans[2] & 0x3c) >> 2); 
//		loop_orig[2] = ((loop_trans[2] & 0x3) << 6) + loop_trans[3]; 
//		for (int j = 0; j < i - 1; j++)ret += loop_orig[j];
//	}return ret;
//}