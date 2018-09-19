#include "stdafx.h"
#include "SystemGraphic.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <GL\glew.h>
#include <GL\GL.h>
#include "Messager.h"
#include "ResourceCache.h"
#include "StringUtil.h"
namespace Engine
{
  SystemGraphic::SystemGraphic(shared_ptr<sf::RenderWindow> renderWindow, shared_ptr<ResourceCache> resourceCache) :
    m_RenderWindow(renderWindow),
    m_ResourceCache(resourceCache)
	{
    Messager::Attach(m_MsgQueue.GetCallback(), Event::Id::RENDER_SPRITE);
	}

	void SystemGraphic::Init()
	{
	}

	void SystemGraphic::Shutdown()
	{
    m_RenderWindow->close();
    Messager::Detach(m_MsgQueue.GetCallback(), Event::Id::RENDER_SPRITE);
	}

	void SystemGraphic::Update(float dt)
	{
    m_RenderWindow->clear();

    auto q = m_MsgQueue.GetQueue();
    while(!q.empty())
    {
      Event &event = q.front();
      q.pop();

			if (event.GetType() == Event::Type::Rendering)
				HandleRenderingEvent(event);
			else
				throw invalid_argument("Unknown rendering event received by SystemGraphic");
    }

    m_RenderWindow->display();
	}

  void SystemGraphic::HandleRenderingEvent(const Event &event)
  {
    switch(event.GetId())
    {
      case Event::Id::RENDER_SPRITE:
      {
        auto resource = m_ResourceCache->GetResource(StringUtil::ToWStr(event.render.resourceName));
        if (resource->GetType() != Resource::Type::Graphic)
          throw invalid_argument("A non-Graphic resource was asked to be rendered: \"" + StringUtil::ToStr(resource->GetName()));

        m_RenderWindow->draw(*static_pointer_cast<sf::Sprite>(resource->GetData()));
        break;
      }
    }
  }
  void SystemGraphic::ResizeWindow(uint width, uint height)
	{
    //TODO: Resize OpenGL viewport glViewport(0, 0, width, height); see https://learnopengl.com/Getting-started/Hello-Window
    if (width * height == 0)
      throw std::invalid_argument("Invalid window size");

    if (width > 1920 || height > 1080)
      throw std::invalid_argument("Window resize area is too big");

    m_RenderWindow->setSize(sf::Vector2u(width, height));
	}

  void SystemGraphic::SetWindowVisible(bool doShow)
  {
    m_RenderWindow->setVisible(doShow);
  }
}