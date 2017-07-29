#pragma once
#include "AppUtil.h"
//=================================================================================================
class InitializerValidator
{
public:
	InitializerValidator(const AppUtil* const appUtil);

	void ValidateThatDiskHaveEnoughSpace(const int64 diskSpaceNeededByte) const;
	void ValidateThatWeHaveEnoughPhysicalRAM(const int64 physicalRAMNeededByte) const;
	void ValidateThatWeHaveEnoughVirtualRAM(const int64 virtualRAMNeededByte) const;
	void ValidateThatWeHaveEnoughContinuousVirtualRAM(const int64 virtualRAMNeededByte) const;
	void ValidateThatProcessIsTheOnlyInstance(const std::wstring &processName) const;
	void ValidateThatCPUIsFastEnough(const MegaHertz minimumCPUFrequency) const;
private:
	const AppUtil* const m_pAppUtil;
};
//=================================================================================================