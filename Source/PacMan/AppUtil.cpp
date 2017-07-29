#include "stdafx.h"
#include "AppUtil.h"
#include "WindowsInclude.h"
//=================================================================================================
const int64 AppUtil::GetDiskSpaceByte() const
{
	const int  drive = _getdrive();
	struct _diskfree_t diskfree;

	_getdiskfree(drive, &diskfree);

	return diskfree.avail_clusters * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
}
//=================================================================================================
const bool AppUtil::IsProcessUniqueInstance(const std::wstring &processName) const
{
	HWND windowHandle = FindWindow(processName.c_str(), NULL);
	if (windowHandle)
	{
		CloseHandle(windowHandle);
		return true;
	}

	return false;
}
//=================================================================================================
const int64 AppUtil::GetPhysicalRAMByte() const
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}
//=================================================================================================
const int64 AppUtil::GetVirtualRAMByte() const
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	return status.ullAvailVirtual;
}
//=================================================================================================
const MegaHertz AppUtil::GetCpuSpeed() const
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	// Open the key where the proc speed is hidden:
	const long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
		RegQueryValueEx(hKey, L"~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize); // Query the key
	return dwMHz;
}
//=================================================================================================