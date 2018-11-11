#pragma once
#include <string>
using namespace std;
namespace Engine
{
	namespace StringUtil
	{
		string ToStr(const wstring &wstr);
		string ToStr(const char *str);
		wstring ToWStr(const string &str);
	}
}