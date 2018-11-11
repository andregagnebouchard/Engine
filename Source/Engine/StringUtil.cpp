#include "stdafx.h"
#include "FileUtil.h"
namespace Engine
{
	namespace StringUtil
	{
		string ToStr(const wstring &wstr)
		{
			return string(wstr.begin(), wstr.end());
		}
		wstring ToWStr(const string &str)
		{
			return wstring(str.begin(), str.end());
		}

		string ToStr(const char *str)
		{
			return string(str);
		}
	}
}