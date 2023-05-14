#pragma once
#include <Engine/IComponent.h>
#include <SFML\Window.hpp>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class SystemInput
	{
	public:
		SystemInput(const shared_ptr<sf::Window> window);
		~SystemInput() = default;

		void Update();
		void Add(const shared_ptr<IComponent> component);
		void Remove(const shared_ptr<IComponent> component);
	private:
		void SignalKeyEvent(const sf::Event &event);
		const shared_ptr<sf::Window> m_Window; // Input events are pushed in the window
		unordered_map<int, shared_ptr<IComponent>> m_Components;
	};
}