#include "stdafx.h"
#include "SystemInput.h"
#include "Messager.h"
#include "EventDefinition.h"
#include <Engine\IComponent.h>
#include "StringUtil.h"
namespace Engine
{
	SystemInput::SystemInput(const shared_ptr<sf::Window> window) :
		m_Window(window)
	{
	}

	void SystemInput::Update()
	{
		sf::Event event;
		while (m_Window->pollEvent(event))
			if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
				SignalKeyEvent(event);

		// Update all components
		for (const auto &component : m_Components)
			component.second->Update();
	}

	void SystemInput::Add(const shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.emplace(component->GetId(), component);
	}

	void SystemInput::Remove(const shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.erase(component->GetId());
	}

	void SystemInput::SignalKeyEvent(const sf::Event &event)
	{
		const InputEvent::KeyState altKeyState = event.key.alt ? InputEvent::KeyState::Pressed : InputEvent::KeyState::Released;
    const InputEvent::KeyState controlKeyState = event.key.control ? InputEvent::KeyState::Pressed : InputEvent::KeyState::Released;
    const InputEvent::KeyState shiftKeyState = event.key.shift ? InputEvent::KeyState::Pressed : InputEvent::KeyState::Released;
    const InputEvent::KeyState systemKeyState = event.key.system ? InputEvent::KeyState::Pressed : InputEvent::KeyState::Released;

    //sf::Keyboard::key and our events matches 1:1
    // SFML does not differentiate pressed and released key, but we do
	  // We apply an offset to the numerical enum value if it is released to locate its corresponding id
    const int offset = event.type == sf::Event::KeyPressed ? 0 : EventDefinition::KEY_RELEASED_OFFSET;
    const int id = offset + static_cast<int>(event.key.code);
    Messager::Fire(make_shared<InputEvent>(static_cast<Event::Key>(id), altKeyState, controlKeyState, shiftKeyState, systemKeyState));
	}
}