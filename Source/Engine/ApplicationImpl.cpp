#include "stdafx.h"
#include "Engine\ApplicationImpl.h"
#include "SystemGraphic.h"
#include "SystemLogic.h"
#include "SystemAudio.h"
#include "SystemInput.h"
#include "ResourceCache.h"
#include "EngineEntityFactory.h"
#include <thread>
using namespace sf;
using namespace std;

namespace Engine
{
	ApplicationImpl::~ApplicationImpl()
	{
		Shutdown();
	}

	void ApplicationImpl::Init(const ApplicationOption& options, const shared_ptr<IGameEntityFactory> gameEntityFactory)
	{
		if (gameEntityFactory == nullptr) throw invalid_argument("Parameter \"entityFactory\" is nullptr");

		Logger::Init();
		Logger::SetLogLevel(Logger::Level::Debug);

		auto renderWindow = make_shared<sf::RenderWindow>(sf::VideoMode(options.GetWindowWidth(), options.GetWindowHeight()), options.GetWindowName());

		m_ResourceCache = make_shared<ResourceCache>(options.GetResourceNameToFilepath());
		m_SystemGraphic = make_shared<SystemGraphic>(renderWindow, m_ResourceCache);
		m_SystemInput = make_shared<SystemInput>(renderWindow);
		m_SystemLogic = make_shared<SystemLogic>();
		m_SystemAudio = make_shared<SystemAudio>(m_ResourceCache);
		m_EngineEntityFactory = make_shared<EngineEntityFactory>(gameEntityFactory, m_SystemGraphic, m_SystemLogic, m_SystemInput, m_SystemAudio);
		m_SystemGraphic->Init();
		m_SystemAudio->Init();
		m_EngineEntityFactory->Init();
	}

	void ApplicationImpl::Shutdown()
	{
		if (m_SystemGraphic != nullptr) m_SystemGraphic->Shutdown();
		if (m_SystemAudio != nullptr) m_SystemAudio->Shutdown();
		if (m_ResourceCache != nullptr) m_ResourceCache->Clear();
		if (m_EngineEntityFactory != nullptr) m_EngineEntityFactory->Shutdown();
	}
	void ApplicationImpl::RunLoop()
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

	void ApplicationImpl::Resize(unsigned int width, unsigned int height)
	{
		//TODO: Resize OpenGL viewport glViewport(0, 0, width, height); see https://learnopengl.com/Getting-started/Hello-Window
		if (width * height == 0)
			throw std::invalid_argument("Invalid window size");

		if (width > 1920 || height > 1080)
			throw std::invalid_argument("Window resize area is too big");

		m_Window->setSize(sf::Vector2u(width, height));
	}
	void ApplicationImpl::SetVisible(bool isVisible)
	{
		m_Window->setVisible(isVisible);
	}
}