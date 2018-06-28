#include "stdafx.h"
#include "Engine\Application.h""
using namespace sf;

namespace Engine
{
	shared_ptr<IApplication> IApplication::Create()
	{
		return make_shared<Application>();
	}

	void Application::Init()
	{
		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);
	}

  void Application::RunLoop()
	{
	  
	}
}