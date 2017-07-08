#include "stdafx.h"
#include "SDLGLExecutionContext.h"
//=================================================================================================
SDLGLExecutionContext::SDLGLExecutionContext(IProcessEventListener* const processEventListener, SDLGLProcessWindow *processWindow) :
	SDLExecutionContext::SDLExecutionContext(processEventListener),
	m_processWindow(processWindow)
{
}
//=================================================================================================
SDLGLExecutionContext::~SDLGLExecutionContext()
{
	delete m_processWindow;

	if (m_openGlContext != NULL)
		SDL_GL_DeleteContext(m_openGlContext);
}
//=================================================================================================
void SDLGLExecutionContext::Init()
{
	SDLExecutionContext::Init();
	SetOpenGLAttributes();
	m_processWindow->Init();
	CreateOpenGLContext();
}
//=================================================================================================
void SDLGLExecutionContext::CreateOpenGLContext()
{
	m_openGlContext = m_processWindow->CreateOpenGlContext();
	if (m_openGlContext == NULL)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		throw std::exception("ERROR: SDL Init");
	}
}
//=================================================================================================
void SDLGLExecutionContext::SetOpenGLAttributes()
{
	// Version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}
//=================================================================================================
IProcessWindow* const SDLGLExecutionContext::GetProcessWindow() const
{
	return m_processWindow;
}
//=================================================================================================