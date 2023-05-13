#pragma once
#include <Engine\ISystemInput.h>
#include <SFML\Window.hpp>
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
		void Update() override;
		void Add(shared_ptr<IComponent> component) override;
		void Remove(shared_ptr<IComponent> component) override;
	private:
		void SignalKeyEvent(const sf::Event &event);
		shared_ptr<sf::Window> m_Window; // Input events are pushed in the window
		map<int, shared_ptr<IComponent>> m_Components;
	};
}