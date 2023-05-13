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
    SystemGraphic(const shared_ptr<sf::RenderWindow> renderWindow, const shared_ptr<IWindow> window, const shared_ptr<ResourceCache> resourceCache);
    ~SystemGraphic() = default;
		
		// ISystem
    void Init() override;
    void Shutdown() override;
    void Update() override;
		void Add(const shared_ptr<IComponent> component) override;
		void Remove(const shared_ptr<IComponent> component) override;

		// ISystemGraphic
    shared_ptr<IWindow> GetWindow() const override { return m_Window; };
  private:
    void RenderSprite(shared_ptr<Event> event);
    void RenderLine(shared_ptr<Event> event);
    MessageQueue m_MsgQueue;
    shared_ptr<IWindow> m_Window;
		shared_ptr<sf::RenderWindow> m_RenderWindow;
    shared_ptr<ResourceCache> m_ResourceCache;
		map<int, shared_ptr<IComponent>> m_Components;
  };
}