#pragma once
#include <Engine\System.h>
#include <Engine\Typedef.h>
#include <SFML\Window.hpp>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	struct WindowInfo
	{
		uint Width;
		uint Length;
		string Title;
	};

	class GraphicSystem : public System
	{
	public:
		static shared_ptr<GraphicSystem> Create(WindowInfo windowInfo);

		~GraphicSystem() = default;

		void Init() override;
		void Shutdown() override;
		void Update(float dt) override;

		void Resize(uint width, uint height);
	private:
    GraphicSystem(WindowInfo windowInfo);

		WindowInfo m_WindowInfo;
		unique_ptr<sf::Window> m_Window;
	};
}