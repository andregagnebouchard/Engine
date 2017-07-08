#include "stdafx.h"
#include "SDLExecutionContext.h"
//=================================================================================================
SDLExecutionContext::SDLExecutionContext(IProcessEventListener* const processEventListener) :
	m_processEventListener(processEventListener)
{
}
//=================================================================================================
void SDLExecutionContext::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::exception("ERROR: SDL Init");
}
//=================================================================================================
SDLExecutionContext::~SDLExecutionContext()
{
	delete m_processEventListener;
	SDL_Quit();
}
//=================================================================================================
IProcessEventListener* const SDLExecutionContext::GetProcessEventListener() const
{
	return m_processEventListener;
}
//=================================================================================================