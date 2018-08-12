#include "CaesarCipher.h"

std::string Caesar::roll(int key){
	for (int i = 0; i < text.size(); i++) {
		if (!isalpha(text[i]))continue;
		text[i] += key;
		if (((text[i] >= 'a' + key) && (text[i] <= 'z' + key) && (text[i] > 'z')) ||
			(text[i] >= 'A' + key) && (text[i] <= 'Z' + key) && (text[i] > 'Z'))
			text[i] -= 26;
		else if (((text[i] >= 'a' + key) && (text[i] <= 'z' + key) && (text[i] < 'a')) ||
			(text[i] >= 'A' + key) && (text[i] <= 'Z' + key) && (text[i] < 'A'))
			text[i] += 26;
	}
	return text;
}

Caesar::Caesar(std::string txt) :text(txt) {}

std::string Caesar::operator++() {
	return roll(1);
}

std::string Caesar::operator--() {
	return roll(-1);
}

std::string Caesar::operator+=(int bias) {
	return roll(bias);
}

std::string Caesar::operator-=(int bias) {
	return roll(-bias);
}

std::string Caesar::operator=(std::string txt) { text = txt; return text; }
