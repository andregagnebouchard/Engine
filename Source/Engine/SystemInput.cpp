#include "stdafx.h"
#include "SystemInput.h"
#include "Messager.h"
#include "EventDefinition.h"
#include <Engine\IComponent.h>
#include "StringUtil.h"
namespace Engine
{
	SystemInput::SystemInput(shared_ptr<sf::Window> window) :
		m_Window(window)
	{
	}

	void SystemInput::Init()
	{

	}

	void SystemInput::Shutdown()
	{
	}

	void SystemInput::Update(float dt)
	{
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
      case sf::Event::KeyReleased:
				SignalKeyEvent(event);
				break;
			}
		}

		// Update all components
		for (auto &component : m_Components)
			component.second->Update(dt);
	}

	void SystemInput::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in SystemInput");

		m_Components[component->GetId()] = component;
	}

	void SystemInput::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it == m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is not in SystemInput");

		m_Components.erase(component->GetId());
	}

	void SystemInput::SignalKeyEvent(const sf::Event &event)
	{
    auto toKeyState = [&](const bool isPressed) 
    {
      return isPressed ? InputEvent::KeyState::Pressed : InputEvent::KeyState::Released; 
    };

    InputEvent::KeyState altKeyState = toKeyState(event.key.alt);
    InputEvent::KeyState controlKeyState = toKeyState(event.key.control);
    InputEvent::KeyState shiftKeyState = toKeyState(event.key.shift);
    InputEvent::KeyState systemKeyState = toKeyState(event.key.system);

    //sf::Keyboard::key and our events matches 1:1
    // SFML does not differentiate pressed and released key, but we do
	  // We apply an offset to the numerical enum value if it is released to locate its corresponding id
    int offset = event.type == sf::Event::KeyPressed ? 0 : EventDefinition::KEY_RELEASED_OFFSET;
    int id = offset + static_cast<int>(event.key.code);
    Messager::Fire(make_shared<InputEvent>(static_cast<Event::Key>(id), altKeyState, controlKeyState, shiftKeyState, systemKeyState));
	}
}