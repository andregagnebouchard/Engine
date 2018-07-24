#pragma once
#include <Engine\IGraphicSystem.h>
#include <SFML\Window.hpp>
using namespace std;
namespace Engine
{
  class GraphicSystem : public IGraphicSystem
  {
  public:
    GraphicSystem(WindowInfo windowInfo);
    ~GraphicSystem() = default;
		
		// ISystem
    void Init() override;
    void Shutdown() override;
    void Update(float dt) override;

		// IGraphicSystem
    void Resize(uint width, uint height) override;
  private:
    WindowInfo m_WindowInfo;
    shared_ptr<sf::Window> m_Window;
  };
}