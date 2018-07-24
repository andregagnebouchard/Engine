#pragma once
#include <memory>
#include <SFML/Window/Keyboard.hpp>
using namespace std;
namespace Engine
{
	class Event
	{
	public:

		struct KeyEvent
		{
			enum class Type { Pressed, Released};
			Type type;
			sf::Event::KeyEvent event;
		};

		enum class Type
		{
			KeyEvent
		};
		Type GetType() const { return m_Type; }
	private:
		

		Type m_Type;
	};
}