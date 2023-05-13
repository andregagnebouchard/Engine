#include "stdafx.h"
#include <thread>
#include "Engine\Application.h"
#include "SystemGraphic.h"
#include "SystemLogic.h"
#include "SystemAudio.h"
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

	void Application::Init(shared_ptr<IApplicationOption> options, shared_ptr<IEntityFactory> entityFactory)
	{
		if (options == nullptr) throw invalid_argument("Parameter \"options\" is nullptr");
		if (entityFactory == nullptr) throw invalid_argument("Parameter \"entityFactory\" is nullptr");

		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);

    // Read WindowInfo from the options
    auto renderWindow = make_shared<sf::RenderWindow>(sf::VideoMode(options->GetWindowWidth(), options->GetWindowHeight()), options->GetWindowName());

    m_ResourceCache = make_shared<ResourceCache>(options->GetResourceNameToFilepath());
    m_SystemGraphic = make_shared<SystemGraphic>(renderWindow, make_shared<Window>(renderWindow), m_ResourceCache);
    m_SystemInput = make_shared<SystemInput>(renderWindow);
		m_SystemLogic = make_shared<SystemLogic>();
		m_SystemAudio= make_shared<SystemAudio>(m_ResourceCache);
		m_EntityFactory = make_shared<EntityFactory>(entityFactory, m_SystemGraphic, m_SystemLogic, m_SystemInput, m_SystemAudio);
		m_SystemGraphic->Init();
		m_SystemInput->Init();
		m_SystemLogic->Init();
		m_SystemAudio->Init();
		m_EntityFactory->Init();
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
			float elapsedNs = static_cast<float>((clock::now() - earlier).count());
			if (elapsedNs < nanoSecondPerFrame) // 
				this_thread::sleep_for(chrono::nanoseconds(nanoSecondPerFrame - static_cast<int>(elapsedNs)));
			earlier = clock::now();

			m_EntityFactory->Update();
			m_SystemInput->Update();
			m_SystemLogic->Update();
			m_SystemGraphic->Update();
			m_SystemAudio->Update();
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
	shared_ptr<ISystemAudio> Application::GetSystemAudio() const
	{
		if (!m_SystemAudio) throw std::exception("Uninitialized SystemAudio");
		return m_SystemAudio;
	}
}