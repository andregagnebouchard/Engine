#pragma once
#include <Engine\ISystemGraphic.h>
#include <Engine\IWindow.h>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Messager.h"
using namespace std;
namespace Engine
{
  class ResourceCache;
	class IWindow;
  class SystemGraphic : public ISystemGraphic
  {
  public:
    SystemGraphic(shared_ptr<sf::RenderWindow> renderWindow, shared_ptr<IWindow> window, shared_ptr<ResourceCache> resourceCache);
    ~SystemGraphic() = default;
		
		// ISystem
    void Init() override;
    void Shutdown() override;
    void Update(float dt) override;
		void Add(shared_ptr<IComponent> component) override;


		// ISystemGraphic
		shared_ptr<IWindow> GetWindow() const override;
  private:
    void HandleRenderingEvent(shared_ptr<RenderEvent> event);
    MessageQueue m_MsgQueue;
    shared_ptr<IWindow> m_Window;
		shared_ptr<sf::RenderWindow> m_RenderWindow;
    shared_ptr<ResourceCache> m_ResourceCache;
		map<int, shared_ptr<IComponent>> m_Components;
  };
}