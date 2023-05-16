#include "stdafx.h"
#include "ApplicationWindow.h"
namespace Engine
{
	ApplicationWindow::ApplicationWindow(const shared_ptr<sf::Window> window) :
		m_Window(window)
	{
	}

	void ApplicationWindow::Resize(unsigned int width, unsigned int height)
	{
		//TODO: Resize OpenGL viewport glViewport(0, 0, width, height); see https://learnopengl.com/Getting-started/Hello-Window
		if (width * height == 0)
			throw std::invalid_argument("Invalid window size");

		if (width > 1920 || height > 1080)
			throw std::invalid_argument("Window resize area is too big");

		m_Window->setSize(sf::Vector2u(width, height));
	}
	void ApplicationWindow::SetVisible(bool isVisible)
	{
		m_Window->setVisible(isVisible);
	}
}