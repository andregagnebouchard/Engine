#pragma once
using namespace std;
namespace Engine
{
	namespace FileUtil
	{
		// Throw if the file does not exist
		unsigned int GetFileSizeByte(const string &fullPath);
		unsigned int GetFileSizeByte(const wstring &fullPath);

		// Return everything after the last dot
		// Guarentee that everything is in lower-case
		wstring GetExtension(const wstring &fullpath);
	}
}