#pragma once
#include <Engine\ISystemInput.h>
#include <SFML\Window.hpp>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class SystemInput : public ISystemInput
	{
	public:
		SystemInput(const shared_ptr<sf::Window> window);
		~SystemInput() = default;

		// ISystem
		void Init() override {};
		void Shutdown() override {};
		void Update() override;
		void Add(const shared_ptr<IComponent> component) override;
		void Remove(const shared_ptr<IComponent> component) override;
	private:
		void SignalKeyEvent(const sf::Event &event);
		const shared_ptr<sf::Window> m_Window; // Input events are pushed in the window
		unordered_map<int, shared_ptr<IComponent>> m_Components;
	};
}