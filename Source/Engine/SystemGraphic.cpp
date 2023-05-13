#include "stdafx.h"
#include "SystemGraphic.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
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
  SystemGraphic::SystemGraphic(const shared_ptr<sf::RenderWindow> renderWindow, const shared_ptr<IWindow> window, const shared_ptr<ResourceCache> resourceCache) :
    m_Window(window),
    m_ResourceCache(resourceCache),
		m_RenderWindow(renderWindow)
	{
	}

	void SystemGraphic::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::RENDER_LINE)));
	}

	void SystemGraphic::Shutdown()
	{
    Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::RENDER_LINE)));
	}

	void SystemGraphic::Update()
	{
		// Clear the screen to black
    m_RenderWindow->clear();

		// Update all components first so they can fire their render event
		for (const auto &component : m_Components)
			component.second->Update();

    while(!m_MsgQueue.Empty())
    {
      const shared_ptr<Event> &event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			const EventDefinition::Id eventId = static_cast<EventDefinition::Id>(event->GetKey().first);
			if (eventId == EventDefinition::Id::RENDER_SPRITE)
				RenderSprite(event);
			else if (eventId == EventDefinition::Id::RENDER_LINE)
				RenderLine(event);
    }
    m_RenderWindow->display();
	}

	void SystemGraphic::Add(const shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.emplace(component->GetId(), component);
	}

	void SystemGraphic::Remove(const shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.erase(component->GetId());
	}

	void SystemGraphic::RenderSprite(const shared_ptr<Event> event)
	{
		const auto ev = dynamic_pointer_cast<RenderSpriteEvent>(event);
		Resource* resource = m_ResourceCache->GetResource((ev->GetResourceName()));
		if (resource->GetType() != Resource::Type::Graphic)
			throw invalid_argument("A non-Graphic resource was asked to be rendered: \"" + StringUtil::ToStr(resource->GetName()));

		const GraphicResource* const graphicResource = dynamic_cast<GraphicResource*>(resource);

		sf::Sprite* sprite = graphicResource->GetSprite();
		sprite->setPosition(sf::Vector2f(ev->GetXPosition(), ev->GetYPosition()));
		sprite->setOrigin(16, 16); // All sprites are 32x32. Center them

		m_RenderWindow->draw(*sprite);
	}

	// WIP for render debug lines
	int render_line_count = 0;
	void SystemGraphic::RenderLine(const shared_ptr<Event> event)
	{
		auto ev = dynamic_pointer_cast<RenderLineEvent>(event);
		if (render_line_count == 1)
			return;
		sf::Vertex line[] =
		{
				sf::Vertex(sf::Vector2f(10, 10)),
				sf::Vertex(sf::Vector2f(150, 150))
		};

		//m_RenderWindow->draw(line, 2, sf::Lines);
		render_line_count++;

		//sf::RectangleShape rectangle(sf::Vector2f(1, 200));
		//m_RenderWindow->draw(rectangle);
	}
}