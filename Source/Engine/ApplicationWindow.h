#pragma once
#include <Engine\IWindow.h>
#include <SFML\Window\Window.hpp>
#include <memory>
using namespace std;
namespace Engine
{
	class ApplicationWindow : public IWindow
	{
	public:
		ApplicationWindow(const shared_ptr<sf::Window> window);
		~ApplicationWindow() = default;

		void Resize(uint width, uint height) override;
		void SetVisible(bool isVisible) override;
	private:
		const shared_ptr<sf::Window> m_Window;
	};
}