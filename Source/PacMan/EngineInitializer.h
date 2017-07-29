#pragma once
#include "InitializerValidator.h"
//=================================================================================================
class EngineInitializer
{
public:
	EngineInitializer(const InitializerValidator* initializerValidator);
	~EngineInitializer();

	void Initialize();

private:
	void ValidateStartup() const;

	const InitializerValidator* m_pInitializerValidator;
};
//=================================================================================================