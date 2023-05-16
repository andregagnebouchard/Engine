#pragma once
#include <Engine\IComponent.h>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Messager.h"
#include <unordered_map>
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
		void Add(const shared_ptr<IComponent> component);
		void Remove(const shared_ptr<IComponent> component);
  private:
    void RenderSprite(shared_ptr<Event> event);
    void RenderLine(shared_ptr<Event> event);
    MessageQueue m_MsgQueue;
		shared_ptr<sf::RenderWindow> m_RenderWindow;
    shared_ptr<ResourceCache> m_ResourceCache;
		unordered_map<int, shared_ptr<IComponent>> m_Components;
  };
}