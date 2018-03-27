#include "stdafx.h"
#include <Engine\Application.h>
using namespace sf;

namespace Engine
{
	shared_ptr<Application> Application::m_Instance = nullptr;
	shared_ptr<Application> Application::Get()
	{
		if (m_Instance == nullptr)
			m_Instance = make_shared<Application>();

		return m_Instance;
	}

	void Application::Init()
	{
		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);
	}
}