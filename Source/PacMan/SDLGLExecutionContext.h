#pragma once
#include "stdafx.h"
#include "SDLExecutionContext.h"
#include "SDLGLProcessWindow.h"
//=================================================================================================
// Massively coupled with SDLGLProcessWindow as SDL did not intend to separate them
class SDLGLExecutionContext : public SDLExecutionContext
{
public:
	~SDLGLExecutionContext();
	SDLGLExecutionContext(IProcessEventListener* const processEventListener, SDLGLProcessWindow *processWindow);

	// IExecutionContext
	virtual IProcessWindow* const GetProcessWindow() const override;

	// SDL
	virtual void Init() override;

private:
	void CreateOpenGLContext();
	void SetOpenGLAttributes();

	SDLGLProcessWindow *m_processWindow;
	SDL_Event m_event;
	SDL_GLContext m_openGlContext;
};
//=================================================================================================