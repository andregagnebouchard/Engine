#pragma once
#include "stdafx.h"
#include <SDL.h>
#include "IExecutionContext.h"
//=================================================================================================
class SDLExecutionContext : public IExecutionContext
{
public:
	SDLExecutionContext(IProcessEventListener* const processEventListener);
	~SDLExecutionContext();

	virtual void Init();

	// IExecutionContext
	virtual IProcessWindow* const GetProcessWindow() const = 0;
	virtual IProcessEventListener* const GetProcessEventListener() const override;

protected:
	IProcessEventListener *m_processEventListener;
private:
};
//=================================================================================================