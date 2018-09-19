#pragma once
#include <Engine\ISystemGraphic.h>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Messager.h"
using namespace std;
namespace Engine
{
  class ResourceCache;
  class SystemGraphic : public ISystemGraphic
  {
  public:
    SystemGraphic(shared_ptr<sf::RenderWindow> renderWindow, shared_ptr<ResourceCache> resourceCache);
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
    shared_ptr<sf::RenderWindow> m_RenderWindow;
    shared_ptr<ResourceCache> m_ResourceCache;
  };
}