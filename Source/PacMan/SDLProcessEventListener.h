#pragma once
//=================================================================================================
#include "stdafx.h"
#include "IProcessEventListener.h"
#include "SDL\SDL.h"
class SDLProcessEventListener : public IProcessEventListener
{
public:
	virtual void Listen() override;
private:
	SDL_Event m_event;
};
//=================================================================================================