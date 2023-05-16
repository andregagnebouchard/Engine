#include "stdafx.h"
#include "Engine\Application.h"
#include "SystemGraphic.h"
#include "SystemLogic.h"
#include "SystemAudio.h"
#include "ApplicationWindow.h"
#include "SystemInput.h"
#include "ResourceCache.h"
#include "EngineEntityFactory.h"
#include <thread>
using namespace sf;
using namespace std;

namespace Engine
{
	Application::~Application()
	{
		Shutdown();
	}

	void Application::Init(const shared_ptr<ApplicationOption> options, const shared_ptr<IGameEntityFactory> gameEntityFactory)
	{
		if (options == nullptr) throw invalid_argument("Parameter \"options\" is nullptr");
		if (gameEntityFactory == nullptr) throw invalid_argument("Parameter \"entityFactory\" is nullptr");

		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);

    auto renderWindow = make_shared<sf::RenderWindow>(sf::VideoMode(options->GetWindowWidth(), options->GetWindowHeight()), options->GetWindowName());

    m_ResourceCache = make_shared<ResourceCache>(options->GetResourceNameToFilepath());
    m_SystemGraphic = make_shared<SystemGraphic>(renderWindow, make_shared<ApplicationWindow>(renderWindow), m_ResourceCache);
    m_SystemInput = make_shared<SystemInput>(renderWindow);
		m_SystemLogic = make_shared<SystemLogic>();
		m_SystemAudio= make_shared<SystemAudio>(m_ResourceCache);
		m_EngineEntityFactory = make_shared<EngineEntityFactory>(gameEntityFactory, m_SystemGraphic, m_SystemLogic, m_SystemInput, m_SystemAudio);
		m_SystemGraphic->Init();
		m_SystemAudio->Init();
		m_EngineEntityFactory->Init();
	}

	void Application::Shutdown()
	{
		if(m_SystemGraphic != nullptr) m_SystemGraphic->Shutdown();
		if(m_SystemAudio != nullptr) m_SystemAudio->Shutdown();
		if(m_ResourceCache != nullptr) m_ResourceCache->Clear();
		if(m_EngineEntityFactory != nullptr) m_EngineEntityFactory->Shutdown();
	}
  void Application::RunLoop()
	{
		using clock = chrono::high_resolution_clock;

		auto earlier = clock::now();
		while (true)
		{
			int64_t elapsedNs = (clock::now() - earlier).count();
			if (elapsedNs < nanoSecondPerFrame) // Sleep until the next frame if we were too fast
				this_thread::sleep_for(chrono::nanoseconds(nanoSecondPerFrame - elapsedNs));
			earlier = clock::now();

			m_EngineEntityFactory->Update();
			m_SystemInput->Update();
			m_SystemLogic->Update();
			m_SystemGraphic->Update();
			m_SystemAudio->Update();
		}
	}
}