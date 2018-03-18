#include "stdafx.h"
#include "DisplayFactory.h"
#include "SDLGLExecutionContext.h"
#include "OpenGLGraphic.h"
#include "SDLProcessEventListener.h"
//=================================================================================================
Display *DisplayFactory::SDLGL_CreateDisplay(const ProcessWindowProperties &initialProcessWindowProperties)
{
	SDLProcessEventListener* sdlProcessEventListener = new SDLProcessEventListener();
	SDLGLProcessWindow *sdlglProcessWindow = new SDLGLProcessWindow(initialProcessWindowProperties);
	SDLGLExecutionContext *sdlglExecutionContext = new SDLGLExecutionContext(sdlProcessEventListener, sdlglProcessWindow);
	OpenGLGraphic *openglGraphic = new OpenGLGraphic();

	sdlglExecutionContext->Init();
	openglGraphic->Init();
	return new Display(sdlglExecutionContext, openglGraphic);
}
//=================================================================================================