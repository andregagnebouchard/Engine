#pragma once
#include <string>
using namespace std;
namespace Engine
{
	namespace StringUtil
	{
		string ToStr(const wstring &wstr);
		wstring ToWStr(const string &str);
	}
}