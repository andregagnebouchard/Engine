#pragma once
#include "stdafx.h"
#include <..\Engine\Include\Engine\System.h>
#include <SFML\Window.hpp>
namespace Engine
{
	struct WindowInfo
	{
		uint width;
		uint length;
		sf::String title;
	};

	class GraphicSystem : public System
	{
	public:
		static shared_ptr<GraphicSystem> Create(WindowInfo windowInfo);
		GraphicSystem(WindowInfo windowInfo);

		~GraphicSystem() = default;

		void Init() override;
		void Shutdown() override;
		void Update() override;

		void Resize(uint width, uint height);
	private:

		WindowInfo m_WindowInfo;
		unique_ptr<sf::Window> m_Window;
	};
}