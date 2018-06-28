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

    void Init() override;
    void Shutdown() override;
    void Update(float dt) override;

    void Resize(uint width, uint height);
  private:
    WindowInfo m_WindowInfo;
    unique_ptr<sf::Window> m_Window;
  };
}