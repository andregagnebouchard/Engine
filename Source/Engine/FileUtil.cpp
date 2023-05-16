#include "stdafx.h"
#include "FileUtil.h"
#include "StringUtil.h"
using namespace std;
namespace Engine
{
	namespace FileUtil
	{
		unsigned int GetFileSizeByte(const string &fullPath)
		{
			struct stat stat_buf;
			const int rc = stat(fullPath.c_str(), &stat_buf);

			if (rc == -1)
				throw invalid_argument("No file at location:" + fullPath);

			return stat_buf.st_size;
		}

		unsigned int GetFileSizeByte(const wstring &fullPath)
		{
			const string strFileName(fullPath.begin(), fullPath.end());
			return GetFileSizeByte(strFileName);
		}

		wstring GetExtension(const wstring &fullpath)
		{
			// Get everything after the last point
			const size_t i = fullpath.rfind(L'.', fullpath.length());
			if (i == wstring::npos)
				throw invalid_argument("The following file has no extenstion:" + StringUtil::ToStr(fullpath));

			wstring ext = fullpath.substr(i + 1, fullpath.length() - i);
			transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
			return ext;
		}
	}
}