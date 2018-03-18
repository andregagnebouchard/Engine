#include "stdafx.h"
#include "SDLProcessEventListener.h"
//=================================================================================================
void SDLProcessEventListener::Listen()
{
	SDL_WaitEvent(&m_event);
}
//=================================================================================================