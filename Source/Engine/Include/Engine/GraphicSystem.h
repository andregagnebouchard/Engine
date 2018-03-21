#pragma once
#include <Engine\System.h>
#include <Engine\Export.h>
#include <SFML\Window.hpp>
#include <memory>
namespace Engine
{
	struct EXPORT WindowInfo
	{
		uint width;
		uint length;
		string title;
	};

	class EXPORT GraphicSystem : public System
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