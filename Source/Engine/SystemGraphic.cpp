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
#include <Engine\IComponent.h>
#include "EventDefinition.h"
namespace Engine
{
  SystemGraphic::SystemGraphic(shared_ptr<sf::RenderWindow> renderWindow, shared_ptr<IWindow> window, shared_ptr<ResourceCache> resourceCache) :
    m_Window(window),
    m_ResourceCache(resourceCache),
		m_RenderWindow(renderWindow)
	{
    Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)));
	}

	void SystemGraphic::Init()
	{
	}

	void SystemGraphic::Shutdown()
	{
    Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)));
	}

	void SystemGraphic::Update(float dt)
	{
    m_RenderWindow->clear();

		// Update all components first so they can fire their render event
		for (auto &component : m_Components)
			component.second->Update(dt);

    while(!m_MsgQueue.Empty())
    {
      shared_ptr<Event> &event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			if (event->GetType() == Event::Type::Render)
				HandleRenderingEvent(dynamic_pointer_cast<RenderEvent>(event));
			else
				throw invalid_argument("Unknown rendering event received by SystemGraphic");
    }
    m_RenderWindow->display();
	}

	void SystemGraphic::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in SystemGraphic");

		m_Components[component->GetId()] = component;
	}

	void SystemGraphic::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it == m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is not in SystemGraphic");

		m_Components.erase(component->GetId());
	}

  void SystemGraphic::HandleRenderingEvent(shared_ptr<RenderEvent> event)
  {
    switch(static_cast<EventDefinition::Id>(event->GetKey().first))
    {
      case EventDefinition::Id::RENDER_SPRITE:
      {
        Resource* resource = m_ResourceCache->GetResource((event->GetResourceName()));
        if (resource->GetType() != Resource::Type::Graphic)
          throw invalid_argument("A non-Graphic resource was asked to be rendered: \"" + StringUtil::ToStr(resource->GetName()));

				GraphicResource* graphicResource= dynamic_cast<GraphicResource*>(resource);

				sf::Sprite* sprite = graphicResource->GetSprite();
				sprite->setPosition(sf::Vector2f(event->GetXPosition(), event->GetYPosition()));

        m_RenderWindow->draw(*sprite);
        break;
      }
    }
  }

	shared_ptr<IWindow> SystemGraphic::GetWindow() const
	{
		return m_Window;
	}
}