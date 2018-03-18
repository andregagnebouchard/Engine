#include "stdafx.h"
#include "Startup.h"
#include "WindowsInclude.h"
#include "Application.h"
using namespace Engine;
//=================================================================================================
bool Startup::CheckStorage(const int64 diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;

	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters = diskSpaceNeeded / (diskfree.sectors_per_cluster*diskfree.bytes_per_sector);

	if (diskfree.avail_clusters < neededClusters)
	{
		// If you get here you don’t have enough disk space!
		theApp->GetLogger().Log("CheckStorage Failure: Not enough physical storage", LogLevel::LOG_ERROR);
		return false;
	}
	return true;
}
//=================================================================================================
ulong Startup::ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		// query the key:
		RegQueryValueEx(hKey, L"~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;
}
//=================================================================================================
bool Startup::CheckMemory(const uint64 physicalRAMNeeded, const uint64 virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded)
	{
		// you don’t have enough physical memory. Tell the player to go get a real 
		// computer and give this one to his mother. 
		theApp->GetLogger().Log("CheckMemory Failure: Not enough physical memory.", LogLevel::LOG_ERROR);
		return false;
	}

	// Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded)
	{
		// you don’t have enough virtual memory available. 
		// Tell the player to shut down the copy of Visual Studio running in the
		// background, or whatever seems to be sucking the memory dry.
		theApp->GetLogger().Log("CheckMemory Failure: Not enough virtual memory.", LogLevel::LOG_ERROR);
		return false;
	}

	char *buff = NEW char[(unsigned int)virtualRAMNeeded];
	if (buff)
		delete[] buff;
	else
	{
		// even though there is enough memory, it isn’t available in one 
		// block, which can be critical for games that manage their own memory
		theApp->GetLogger().Log("CheckMemory Failure: Not enough contiguous available memory.", LogLevel::LOG_ERROR);
		return false;
	}
	return true;
}
//=================================================================================================
bool Startup::IsOnlyInstance(const sf::String &gameTitle)
{
	// Find the window.  If active, set and return false
	// Only one game instance may have this mutex at a time...
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle.toWideString().c_str());

	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle.toWideString().c_str(), NULL);
		if (hWnd)
		{
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}
//=================================================================================================