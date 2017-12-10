#include "stdafx.h"
#include "TimeTool.h"


#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <locale>


#include <time.h>

namespace time_tool
{
	std::time_t GetTimeFromString(const std::wstring & s)
	{

		struct std::tm tm = { 0 };
		if (6 != swscanf_s(s.c_str(), L"%d-%d-%d %d:%d:%d",
			&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
			&tm.tm_hour, &tm.tm_min, &tm.tm_sec))
			throw std::runtime_error("error GetTimeFromString");
		tm.tm_year -= 1900;
		tm.tm_mon -= 1;
		return mktime(&tm);
	}

	std::wstring TimeToString(const time_t time)
	{
		tm tm = { 0 };
		localtime_s(&tm,&time);
		wchar_t time_buffer[60] = { 0 };
		//_wasctime_s(time_buffer, &tm);
		swprintf_s(time_buffer, L"%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		return time_buffer;
	}

}