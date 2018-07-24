#include "stdafx.h"
#include "SystemInput.h"
#include "Messager.h"
namespace Engine
{
	/*
	shared_ptr<SystemInput> ISystemInput::Create()
	{
		return make_shared<SystemInput>();
	}
	*/

	SystemInput::SystemInput(shared_ptr<sf::Window> window) :
		m_Window(window)
	{
	}

	void SystemInput::Init()
	{
		Logger::Log("Created context window", Logger::Level::Info);
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
				SignalKeyEvent(event, Event::KeyEvent::State::Pressed);
				break;
			case sf::Event::KeyReleased:
				SignalKeyEvent(event, Event::KeyEvent::State::Released);
				break;
			}
		}
	}

	void SystemInput::SignalKeyEvent(const sf::Event &event, Event::KeyEvent::State state)
	{
    //Messager::Fire(event);
	}
}