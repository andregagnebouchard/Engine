#include "stdafx.h"
#include "FileUtil.h"
#include "StringUtil.h"
namespace Engine
{
	namespace FileUtil
	{
		Byte GetFileSize(const string &fullPath)
		{
			struct stat stat_buf;
			int rc = stat(fullPath.c_str(), &stat_buf);

			if (rc == -1)
				throw std::invalid_argument("No file at location:" + fullPath);

			return stat_buf.st_size;
		}

		Byte GetFileSize(const wstring &fullPath)
		{
			string strFileName(fullPath.begin(), fullPath.end());
			return GetFileSize(strFileName);
		}

		wstring GetExtension(const wstring &fullpath)
		{
			size_t i = fullpath.rfind(L'.', fullpath.length());
			if (i == wstring::npos)
				throw std::invalid_argument("The following file has no extenstion:" + StringUtil::ToStr(fullpath));

			wstring ext = fullpath.substr(i + 1, fullpath.length() - i);
			transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
			return ext;
		}
	}
}