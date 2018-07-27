#include "stdafx.h"
#include "Engine\Application.h""
#include "SystemGraphic.h"
#include "SystemInput.h"
using namespace sf;

namespace Engine
{
	shared_ptr<IApplication> IApplication::Create()
	{
		return make_shared<Application>();
	}

	void Application::Init()
	{
		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);

    // Read WindowInfo from a config file
    auto window = make_shared<sf::Window>(sf::VideoMode(1024, 768), sf::String("Engine"));
    m_SystemGraphic = make_shared<SystemGraphic>(window);
    m_SystemInput = make_shared<SystemInput>(window);
	}

  void Application::RunLoop()
	{
	  
	}

  shared_ptr<ISystemInput> Application::GetSystemInput() const
	{
    if (!m_SystemInput) throw std::exception("Uninitialized SystemInput");
    return m_SystemInput;
	}

  shared_ptr<ISystemGraphic> Application::GetSystemGraphic() const
  {
    if (!m_SystemGraphic) throw std::exception("Uninitialized SystemGraphic");
    return m_SystemGraphic;
  }
}