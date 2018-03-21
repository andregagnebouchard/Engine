#include "stdafx.h"
#include <Engine\GraphicSystem.h>

namespace Engine
{
	shared_ptr<GraphicSystem> GraphicSystem::Create(WindowInfo windowInfo)
	{
		return make_shared<GraphicSystem>(windowInfo);
	}

	GraphicSystem::GraphicSystem(WindowInfo windowInfo) :
		m_WindowInfo(windowInfo)
	{

	}
	void GraphicSystem::Init()
	{
		m_Window = make_unique<sf::Window>(sf::VideoMode(m_WindowInfo.width, m_WindowInfo.length), sf::String(m_WindowInfo.title));
		Logger::Log("Created context window", Logger::Level::Info);
	}

	void GraphicSystem::Shutdown()
	{

	}

	void GraphicSystem::Update()
	{

	}
}