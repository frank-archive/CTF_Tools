#include"HTTPToolkit.h"
#include"Logger.h"

std::string & HTTPConstructor::operator[](std::string key) {
	return table[key];
}

std::string HTTPConstructor::toString() {
	Logger tlog; tlog.debug("constructing http message\n");
	if (table.find("Host") == table.end()) {
		tlog.error("Host not specified\n");
		return "";
	}

}
