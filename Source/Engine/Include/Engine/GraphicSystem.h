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
    WindowInfo() = default;
    ~WindowInfo() = default;
    WindowInfo(const WindowInfo& w) = default;

		uint width;
		uint length;
		string title;
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