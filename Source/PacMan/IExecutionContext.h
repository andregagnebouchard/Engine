#pragma once
#include "stdafx.h"
#include "IProcessWindow.h"
#include "IProcessEventListener.h"
//=================================================================================================
class IExecutionContext
{
public:
	virtual ~IExecutionContext() {};

	virtual IProcessWindow* const GetProcessWindow() const = 0;
	virtual IProcessEventListener* const GetProcessEventListener() const = 0;
};
//=================================================================================================