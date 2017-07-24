#pragma once
#include "stdafx.h"
//=================================================================================================
class InitializerValidator
{
public:
	void ValidateIfDiskHaveEnoughSpace(const int64 diskSpaceNeeded);
	MegaHertz ReadCPUFrequency();
	bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	bool VerifyOnlyInstance(LPCTSTR gameTitle);
	const TCHAR *GetSaveGameDirectory(HWND hWnd, const TCHAR *gameAppDirectory);
	bool CheckForJoystick(HWND hWnd);
private:
	const int64 GetDiskSpaceSpace() const;
}
//=================================================================================================