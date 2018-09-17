#pragma once
#include "Engine\Typedef.h"
using namespace std;
namespace Engine
{
	namespace FileUtil
	{
		// Throw if the file does not exist
		Byte GetFileSize(const string &fullPath);
		Byte GetFileSize(const wstring &fullPath);

		// Return everything after the last dot
		// Guarentee that everything is in lower-case
		wstring GetExtension(const wstring &fullpath);
	}
}