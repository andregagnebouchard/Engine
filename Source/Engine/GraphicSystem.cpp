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
		m_Window = make_unique<sf::Window>(sf::VideoMode(m_WindowInfo.Width, m_WindowInfo.Length), sf::String(m_WindowInfo.Title));
		Logger::Log("Created context window", Logger::Level::Info);
	}

	void GraphicSystem::Shutdown()
	{
    m_Window->close();
    m_Window.reset();
	}

	void GraphicSystem::Update(float dt)
	{

	}

  void GraphicSystem::Resize(uint width, uint height)
	{
    if (width * height == 0)
      throw std::invalid_argument("Invalid window size");

    if (width > 1920 || height > 1080)
      throw std::invalid_argument("Window resize area is too big");

    m_Window->setSize(sf::Vector2u(width, height));
	}
}