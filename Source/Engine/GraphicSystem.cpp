#include "stdafx.h"
#include "GraphicSystem.h"

namespace Engine
{
	shared_ptr<IGraphicSystem> IGraphicSystem::Create(WindowInfo windowInfo)
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
    //TODO: Resize OpenGL viewport glViewport(0, 0, width, height); see https://learnopengl.com/Getting-started/Hello-Window
    if (width * height == 0)
      throw std::invalid_argument("Invalid window size");

    if (width > 1920 || height > 1080)
      throw std::invalid_argument("Window resize area is too big");

    m_Window->setSize(sf::Vector2u(width, height));
	}
}