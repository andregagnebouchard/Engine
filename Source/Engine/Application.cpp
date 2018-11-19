#include "stdafx.h"
#include "Engine\Application.h"
#include "SystemGraphic.h"
#include "SystemLogic.h"
#include "Window.h"
#include "SystemInput.h"
#include "ResourceCache.h"
#include "EntityFactory.h"
using namespace sf;

namespace Engine
{
	Application::~Application()
	{
		Shutdown();
	}
	shared_ptr<IApplication> IApplication::Create()
	{
		return make_shared<Application>();
	}

	void Application::Init(shared_ptr<IApplicationOption> options, shared_ptr<IComponentFactory> componentFactory)
	{
		if (options == nullptr) throw invalid_argument("Parameter \"options\" is nullptr");
		if (componentFactory == nullptr) throw invalid_argument("Parameter \"componentFactory\" is nullptr");

		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);

    // Read WindowInfo from the options
    auto renderWindow = make_shared<sf::RenderWindow>(sf::VideoMode(options->GetWindowWidth(), options->GetWindowHeight()), options->GetWindowName());

		// Read all ressources from the options
    m_ResourceCache = make_shared<ResourceCache>();
    for (auto resource : options->GetResources())
      m_ResourceCache->AddResource(resource);

    m_SystemGraphic = make_shared<SystemGraphic>(renderWindow, make_shared<Window>(renderWindow), m_ResourceCache);
    m_SystemInput = make_shared<SystemInput>(renderWindow);
		m_SystemLogic = make_shared<SystemLogic>();

		// Read all entity definition from the options
		m_EntityFactory = make_shared<EntityFactory>(componentFactory, m_SystemGraphic, m_SystemLogic, m_SystemInput);
		for (auto entity : options->GetEntities())
			m_EntityFactory->RegisterEntity(entity->componentNames, entity->name);
	}

	void Application::Shutdown()
	{
		if(m_SystemGraphic != nullptr) m_SystemGraphic->Shutdown();
		if(m_SystemInput != nullptr) m_SystemInput->Shutdown();
		if(m_SystemLogic != nullptr) m_SystemLogic->Shutdown();
	}
  void Application::RunLoop()
	{
		using clock = std::chrono::high_resolution_clock;

		auto earlier = clock::now();
		while (true)
		{
			float dt = static_cast<float>((clock::now() - earlier).count());
			earlier = clock::now();

			m_EntityFactory->Update(dt);
			m_SystemInput->Update(dt);
			m_SystemLogic->Update(dt);
			m_SystemGraphic->Update(dt);
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

	shared_ptr<ISystemLogic> Application::GetSystemLogic() const
	{
		if (!m_SystemLogic) throw std::exception("Uninitialized SystemGraphic");
		return m_SystemLogic;
	}
}