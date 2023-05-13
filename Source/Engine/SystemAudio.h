#pragma once
#include <Engine\ISystemAudio.h>
#include "Messager.h"
#include <unordered_map>
#include <memory>
using namespace std;
namespace Engine
{
  class ResourceCache;
  class SoundEvent;
  class SystemAudio : public ISystemAudio
  {
  public:
    SystemAudio(const shared_ptr<ResourceCache> resourceCache);
    ~SystemAudio() = default;

    // ISystem
    void Init() override;
    void Shutdown() override;
    void Update() override;
    void Add(const shared_ptr<IComponent> component) override;
    void Remove(const shared_ptr<IComponent> component) override;

  private:
    void HandleAudioEvent(const shared_ptr<AudioEvent> event) const;
    MessageQueue m_MsgQueue;
    const shared_ptr<ResourceCache> m_ResourceCache;
    unordered_map<int, shared_ptr<IComponent>> m_Components;
  };
}