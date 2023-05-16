#include "stdafx.h"
#include "Engine\Application.h"
#include "Engine\ApplicationImpl.h"
using namespace sf;
using namespace std;

namespace Engine
{
	Application::Application() :
		m_Impl(new ApplicationImpl())
	{

	}

	Application::~Application()
	{
		delete m_Impl;
	}

	void Application::Init(const ApplicationOption& options, const shared_ptr<IGameEntityFactory> gameEntityFactory)
	{
		m_Impl->Init(options, gameEntityFactory);
	}

	void Application::Shutdown()
	{
		m_Impl->Shutdown();
	}
  void Application::RunLoop()
	{
		m_Impl->RunLoop();
	}

	void Application::Resize(unsigned int width, unsigned int height)
	{
		m_Impl->Resize(width, height);
	}
	void Application::SetVisible(bool isVisible)
	{
		m_Impl->SetVisible(isVisible);
	}
}