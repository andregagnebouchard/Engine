#pragma once
#include <Engine\IComponent.h>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Messager.h"
#include <unordered_map>
#include <queue>
using namespace std;
namespace Engine
{
  class ResourceCache;
  class IComponent;
  class SystemGraphic
  {
  public:
    SystemGraphic(const shared_ptr<sf::RenderWindow> renderWindow, const shared_ptr<ResourceCache> resourceCache);
    ~SystemGraphic() = default;
		
    void Init();
    void Shutdown();
    void Update();
    void OnEvent(const shared_ptr<Event> event);
		void Add(const shared_ptr<IComponent> component);
		void Remove(const shared_ptr<IComponent> component);
  private:
    void RenderSprite(shared_ptr<Event> event);
    void RenderLine(shared_ptr<Event> event);

    const function<void(shared_ptr<Event>)> m_EventCallback;
		shared_ptr<sf::RenderWindow> m_RenderWindow;
    shared_ptr<ResourceCache> m_ResourceCache;
		unordered_map<int, shared_ptr<IComponent>> m_Components;
  };
}