#include "stdafx.h"
#include "SystemInput.h"
#include "Messager.h"
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
    int offset = event.type == sf::Event::KeyPressed ? 0 : Event::KEY_RELEASED_OFFSET;
    int id = offset + static_cast<int>(event.key.code);
    Messager::Fire(make_shared<InputEvent>(static_cast<Event::Id>(id), altKeyState, controlKeyState, shiftKeyState, systemKeyState));
	}
}