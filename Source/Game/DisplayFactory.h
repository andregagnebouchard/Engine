#pragma once
#include "Display.h"
//=================================================================================================
class DisplayFactory
{
public:
	static Display* SDLGL_CreateDisplay(const ProcessWindowProperties &initialProcessWindowProperties);
};
//=================================================================================================