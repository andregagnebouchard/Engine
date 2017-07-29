#include "stdafx.h"
#include "EngineInitializer.h"
//=================================================================================================
EngineInitializer::EngineInitializer(const InitializerValidator* initializerValidator) :
	m_pInitializerValidator(initializerValidator)
{}
//=================================================================================================
EngineInitializer::~EngineInitializer()
{
	SafeDelete(m_pInitializerValidator);
}
//=================================================================================================
void EngineInitializer::Initialize()
{
	ValidateStartup();
}
//=================================================================================================
void EngineInitializer::ValidateStartup() const
{
	const int64 physicalRAMNeeded = 512 * MEGABYTE;
	const int64 virtualRAMNeeded = 1024 * MEGABYTE;
	const int64 diskSpaceNeeded = 10 * MEGABYTE;
	const MegaHertz CPUFreqNeeded = 1300;
	const std::wstring processName = L"Engine";

	m_pInitializerValidator->ValidateThatDiskHaveEnoughSpace(diskSpaceNeeded);
	m_pInitializerValidator->ValidateThatWeHaveEnoughPhysicalRAM(physicalRAMNeeded);
	m_pInitializerValidator->ValidateThatWeHaveEnoughVirtualRAM(virtualRAMNeeded);
	m_pInitializerValidator->ValidateThatWeHaveEnoughContinuousVirtualRAM(virtualRAMNeeded);
	m_pInitializerValidator->ValidateThatProcessIsTheOnlyInstance(processName.c_str());
	m_pInitializerValidator->ValidateThatCPUIsFastEnough(CPUFreqNeeded);
}
//=================================================================================================