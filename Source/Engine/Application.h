#pragma once
#include "stdafx.h"
#include "Logger.h"
#include <SFML\Window.hpp>
namespace Engine
{
	struct WindowInfo
	{
		uint width;
		uint length;
		sf::String title;
	};

	class Application
	{
	public:
		Application();
		void Init(WindowInfo windowInfo);

		const Logger& GetLogger();
	private:
		Logger m_logger;
		std::unique_ptr<sf::Window> m_window;
	};

}
extern Engine::Application *theApp;
