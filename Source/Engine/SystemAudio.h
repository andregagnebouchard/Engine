#pragma once
#include <Engine/IComponent.h>
#include "Messager.h"
#include <unordered_map>
#include <memory>
using namespace std;
namespace Engine
{
  class ResourceCache;
  class SoundEvent;
  class SystemAudio
  {
  public:
    SystemAudio(const shared_ptr<ResourceCache> resourceCache);
    ~SystemAudio() = default;

    void Init();
    void Shutdown();
    void Update();
    void OnEvent(const shared_ptr<Event> event);
    void Add(const shared_ptr<IComponent> component);
    void Remove(const shared_ptr<IComponent> component);

  private:
    void HandleAudioEvent(const shared_ptr<AudioEvent> event) const;
    const shared_ptr<ResourceCache> m_ResourceCache;
    const function<void(shared_ptr<Event>)> m_EventCallback;
    unordered_map<int, shared_ptr<IComponent>> m_Components;
  };
}