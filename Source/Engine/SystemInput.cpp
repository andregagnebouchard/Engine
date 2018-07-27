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
    Event toFire(Event::Type::Key);

    auto pressedToState = [&](const bool isPressed, Event::KeyEvent::State *state) {isPressed ? *state = Event::KeyEvent::State::Pressed : *state = Event::KeyEvent::State::Released; };
    pressedToState(event.key.alt, &toFire.key.alt);
    pressedToState(event.key.control, &toFire.key.control);
    pressedToState(event.key.shift, &toFire.key.shift);
    pressedToState(event.key.system, &toFire.key.system);

    //sf::Keyboard::key and our events matches 1:1
    // SFML does not differentiate pressed and released key, but we do
	  // We apply an offset to the numerical enum value if it is released to locate its corresponding id
    int offset = event.type == sf::Event::KeyPressed ? 0 : Event::KEY_RELEASED_OFFSET;
    int id = offset + static_cast<int>(event.key.code);
    toFire.SetId(static_cast<Event::Id>(id));
    Messager::Fire(toFire);
	}
}