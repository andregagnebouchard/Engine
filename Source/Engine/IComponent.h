#pragma once

namespace Engine
{
  class IComponent
  {
  public:
    virtual ~IComponent() = default;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Update(float dt) = 0;
  };
}