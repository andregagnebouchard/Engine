#include "stdafx.h"
#include "SDLGLProcessWindow.h"
//=================================================================================================
SDLGLProcessWindow::SDLGLProcessWindow(const ProcessWindowProperties &initialProperties) :
	m_properties(initialProperties)
{
}
//=================================================================================================
SDLGLProcessWindow::~SDLGLProcessWindow()
{
	if (m_window != nullptr)
		SDL_DestroyWindow(m_window);
}
//=================================================================================================
void SDLGLProcessWindow::Init()
{
	m_window = SDL_CreateWindow(m_properties.name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_properties.width,
		m_properties.height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (m_window == NULL)
		throw std::exception("ERROR: Init SDLGLProcessWindow");
}
//=================================================================================================
void SDLGLProcessWindow::UpdateProperties(const ProcessWindowProperties &newProperties)
{
	newProperties;
	throw std::exception("Not implemented");
}
//=================================================================================================
SDL_GLContext SDLGLProcessWindow::CreateOpenGlContext()
{
	return SDL_GL_CreateContext(m_window);
}
//=================================================================================================
void SDLGLProcessWindow::UpdateDisplay()
{
	SDL_GL_SwapWindow(m_window);
}
//=================================================================================================