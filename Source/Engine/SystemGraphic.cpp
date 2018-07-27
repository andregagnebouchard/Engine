#include "stdafx.h"
#include "SystemGraphic.h"
#include "Messager.h"
namespace Engine
{
  SystemGraphic::SystemGraphic(shared_ptr<sf::Window> window) :
    m_Window(window)
	{
    Messager::Attach(m_MsgQueue.GetCallback(), Event::Id::RENDER_SPRITE);
	}

	void SystemGraphic::Init()
	{
	}

	void SystemGraphic::Shutdown()
	{
    m_Window->close();
    Messager::Detach(m_MsgQueue.GetCallback(), Event::Id::RENDER_SPRITE);
	}

	void SystemGraphic::Update(float dt)
	{
    auto q = m_MsgQueue.GetEvents();
    while(!q.empty())
    {
      Event &event = q.front();
      q.pop();

      if (event.GetType() == Event::Type::Rendering)
        HandleRenderingEvent(event);
    }
	}

  void SystemGraphic::HandleRenderingEvent(const Event &event)
  {
    switch(event.GetId())
    {
    case Event::Id::RENDER_SPRITE:
      {
      event.render.spriteId;
      break;
      }
    }
  }
  void SystemGraphic::Resize(uint width, uint height)
	{
    //TODO: Resize OpenGL viewport glViewport(0, 0, width, height); see https://learnopengl.com/Getting-started/Hello-Window
    if (width * height == 0)
      throw std::invalid_argument("Invalid window size");

    if (width > 1920 || height > 1080)
      throw std::invalid_argument("Window resize area is too big");

    m_Window->setSize(sf::Vector2u(width, height));
	}
}