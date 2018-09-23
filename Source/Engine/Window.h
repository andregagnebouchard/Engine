#pragma once
#include <Engine\IWindow.h>
#include <SFML\Window\Window.hpp>
#include <memory>
using namespace std;
namespace Engine
{
	class Window : public IWindow
	{
	public:
		Window(shared_ptr<sf::Window> window);
		~Window() = default;

		void Resize(uint width, uint height) override;
		void SetVisible(bool isVisible) override;
	private:
		shared_ptr<sf::Window> m_Window;
	};
}