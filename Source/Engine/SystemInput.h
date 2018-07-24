#pragma once
#include <Engine\ISystemInput.h>
#include <SFML\Window.hpp>
#include "Event.h"
using namespace std;
namespace Engine
{
	class SystemInput : public ISystemInput
	{
	public:
		SystemInput(shared_ptr<sf::Window> window);
		~SystemInput() = default;

		// ISystem
		void Init() override;
		void Shutdown() override;
		void Update(float dt) override;

	private:
		void SignalKeyEvent(const sf::Event &event, Event::KeyEvent::Type type);
		shared_ptr<sf::Window> m_Window;
	};
}