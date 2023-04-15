#pragma once
#include <Engine\ISystemAudio.h>
#include "Messager.h"
#include <map>
using namespace std;
namespace Engine
{
  class ResourceCache;
  class SoundEvent;
  class SystemAudio : public ISystemAudio
  {
  public:
    SystemAudio(shared_ptr<ResourceCache> resourceCache);
    ~SystemAudio() = default;

    // ISystem
    void Init() override;
    void Shutdown() override;
    void Update(float dt) override;
    void Add(shared_ptr<IComponent> component) override;
    void Remove(shared_ptr<IComponent> component) override;

  private:
    void HandleAudioEvent(shared_ptr<AudioEvent> event);
    MessageQueue m_MsgQueue;
    shared_ptr<ResourceCache> m_ResourceCache;
    map<int, shared_ptr<IComponent>> m_Components;
  };
}