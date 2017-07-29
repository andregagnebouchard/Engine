#pragma once
#include "IProcessWindow.h"
#include "SDLExecutionContext.h"
//=================================================================================================
class SDLGLProcessWindow : public IProcessWindow
{
public:
	SDLGLProcessWindow(const ProcessWindowProperties &initialProperties);
	~SDLGLProcessWindow();

	void Init();

	// IProcessWindow
	virtual void UpdateDisplay() override;
	virtual void UpdateProperties(const ProcessWindowProperties &newProperties) override;

	// IMPL
	SDL_GLContext CreateOpenGlContext();
private:
	ProcessWindowProperties m_properties;
	SDL_Window* m_window;
};
//=================================================================================================