#pragma once
#include<cstdarg>
#include<cstdio>

struct Logger{
#undef ERROR
public:
	enum LogLevel {
		DEBUG, INFO, WARNING, ERROR, CRITICAL
	};
private:
	LogLevel level;
	void v_log(LogLevel level, const char *fmt, va_list list);
public:
	Logger() { level = INFO; }
	void setLevel(LogLevel l) { level = l; }
	void indented(const char *fmt, LogLevel level = INFO, ...);//default:INFO

	void success(const char *fmt, ...);//INFO
	void failure(const char *fmt, ...);//INFO

	void info_once(const char *fmt, ...);//INFO
	void warning_once(const char *fmt, ...);//WARNING
	
	void progress(const char *fmt, ...);//INFO
	void debug(const char *fmt, ...);//DEBUG
	void info(const char *fmt, ...);//INFO
	void warning(const char *fmt, ...);//WARNING
	void error(const char *fmt, ...);//ERROR
	void critical(const char *fmt, ...);//CRITICAL
	void _log(LogLevel level, const char *fmt, ...);
};