#include "stdafx.h"
#include "Application.h"
using namespace Engine;

Application *theApp = nullptr;
//=================================================================================================
Application::Application()
{
	theApp = this;
}
//=================================================================================================
void Application::Init(WindowInfo windowInfo)
{
	m_logger.Init();

	m_window = std::make_unique<sf::Window>(sf::VideoMode(windowInfo.width, windowInfo.length), windowInfo.title);
	m_logger.Log("Created context window", LogLevel::LOG_INFO);

}
//=================================================================================================
const Logger& Application::GetLogger()
{
	return m_logger;
}
//=================================================================================================
