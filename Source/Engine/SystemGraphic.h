#pragma once
#include <Engine\ISystemGraphic.h>
#include <SFML\Window.hpp>
#include "Messager.h"
using namespace std;
namespace Engine
{
  class ResourceCache;
  class SystemGraphic : public ISystemGraphic
  {
  public:
    SystemGraphic(shared_ptr<sf::Window> window, shared_ptr<ResourceCache> resourceCache);
    ~SystemGraphic() = default;
		
		// ISystem
    void Init() override;
    void Shutdown() override;
    void Update(float dt) override;

		// ISystemGraphic
    void ResizeWindow(uint width, uint height) override;
    void SetWindowVisible(bool isVisible) override;
  private:
    void HandleRenderingEvent(const Event &event);
    MessageQueue m_MsgQueue;
    shared_ptr<sf::Window> m_Window;
    shared_ptr<ResourceCache> m_ResourceCache;
  };
}