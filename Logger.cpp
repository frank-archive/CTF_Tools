#include "Logger.h"
#include<vector>

std::vector<std::string>error_log;

void Logger::v_log(LogLevel level, const char * fmt, va_list list){
	if (this->level > level)return;
	vprintf(fmt, list);
}

void Logger::indented(const char * fmt, LogLevel level, ...) {
	_log(level, "    ");
	va_list list;
	va_start(list, level);
	v_log(level, fmt, list);
	va_end(list);
}
void Logger::success(const char * fmt, ...) {
	_log(INFO, "[+] ");
	va_list list;
	va_start(list, fmt);
	v_log(INFO, fmt, list);
	va_end(list);
}
void Logger::failure(const char * fmt, ...) {
	_log(INFO, "[-] ");
	va_list list;
	va_start(list, fmt);
	v_log(INFO, fmt, list);
	va_end(list);
}

void Logger::progress(const char * fmt, ...){
	_log(INFO, "[x] ");
	va_list list;
	va_start(list, fmt);
	v_log(INFO, fmt, list);
	va_end(list);
}

void Logger::debug(const char * fmt, ...) {
	_log(DEBUG, "[DEBUG] ");
	va_list list;
	va_start(list, fmt);
	v_log(DEBUG, fmt, list);
	va_end(list);
}

void Logger::info(const char * fmt, ...) {
	_log(DEBUG, "[*] ");
	va_list list;
	va_start(list, fmt);
	v_log(DEBUG, fmt, list);
	va_end(list);
}

void Logger::error(const char * fmt, ...){
	_log(ERROR, "[ERROR] ");
	char buffer[2048];
	va_list list;
	va_start(list, fmt);
	vsprintf(buffer, fmt, list);
	error_log.push_back(buffer);
	v_log(ERROR, fmt, list);
	va_end(list);
}

void Logger::_log(LogLevel level, const char * fmt, ...){
	if (this->level > level)return;
	va_list list;
	va_start(list, fmt);
	printf(fmt, list);
	va_end(list);
}
