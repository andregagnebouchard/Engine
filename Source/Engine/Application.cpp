#include "stdafx.h"
#include "Engine\Application.h"
#include "SystemGraphic.h"
#include "SystemInput.h"
#include "ResourceCache.h"
using namespace sf;

namespace Engine
{
	shared_ptr<IApplication> IApplication::Create()
	{
		return make_shared<Application>();
	}

	void Application::Init(shared_ptr<IApplicationOption> options)
	{
		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);

    // Read WindowInfo from a config file
    auto window = make_shared<sf::RenderWindow>(sf::VideoMode(options->GetWindowWidth(), options->GetWindowHeight()), options->GetWindowName());

    m_ResourceCache = make_shared<ResourceCache>();
    for (auto resource : options->GetResources())
      m_ResourceCache->AddResource(resource);

    m_SystemGraphic = make_shared<SystemGraphic>(window, m_ResourceCache);
    m_SystemInput = make_shared<SystemInput>(window);
	}

	void Application::Shutdown()
	{
		m_SystemGraphic->Shutdown();
		m_SystemInput->Shutdown();
	}
  void Application::RunLoop()
	{
		using clock = std::chrono::high_resolution_clock;

		auto earlier = clock::now();
		while (true)
		{
			auto dt = clock::now() - earlier;
			earlier = clock::now();

			m_SystemInput->Update(static_cast<float>(dt.count()));
			m_SystemGraphic->Update(static_cast<float>(dt.count()));
		}
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