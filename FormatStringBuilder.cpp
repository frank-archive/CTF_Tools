#include "FormatStringBuilder.h"

void FSBuilder::read(int offset, type as) {
	constructed += "%" + std::to_string(offset);
	constructed += index[as];
}

std::string FSBuilder::result() {
	return constructed;
}
