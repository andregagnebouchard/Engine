#include "stdafx.h"
#include "InitializerValidator.h"
//=================================================================================================
InitializerValidator::InitializerValidator(const AppUtil* const appUtil) :
	m_pAppUtil(appUtil)
{
}
//=================================================================================================
void InitializerValidator::ValidateThatDiskHaveEnoughSpace(const int64 diskSpaceNeededByte) const
{
	if (m_pAppUtil->GetDiskSpaceByte() < diskSpaceNeededByte)
		throw std::exception("Disks doesn't have enough space");
}
//=================================================================================================
void InitializerValidator::ValidateThatWeHaveEnoughPhysicalRAM(const int64 physicalRAMNeededByte) const
{
	if (m_pAppUtil->GetPhysicalRAMByte() < physicalRAMNeededByte)
		throw std::exception("Not enough physical RAM");
}
//=================================================================================================
void InitializerValidator::ValidateThatWeHaveEnoughVirtualRAM(const int64 virtualRAMNeededByte) const
{
	if (m_pAppUtil->GetVirtualRAMByte() < virtualRAMNeededByte)
		throw std::exception("Not enough virtual RAM");
}
//=================================================================================================
void InitializerValidator::ValidateThatWeHaveEnoughContinuousVirtualRAM(const int64 virtualRAMNeededByte) const
{
	char *buff = new char[(unsigned int)virtualRAMNeededByte];
	if (buff)
		delete[] buff;
	else
		throw std::exception("Not enough contiguous available memory.");
}
//=================================================================================================
void InitializerValidator::ValidateThatProcessIsTheOnlyInstance(const std::wstring &processName) const
{
	if (m_pAppUtil->IsProcessUniqueInstance(processName) == false)
		throw std::exception("An instance of the process already exists");
}
//=================================================================================================
void InitializerValidator::ValidateThatCPUIsFastEnough(const MegaHertz minimumCPUFrequency) const
{
	if (m_pAppUtil->GetCpuSpeed() < minimumCPUFrequency)
		throw std::exception("CPU is too slow to launch the process");
}
//=================================================================================================