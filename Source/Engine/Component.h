#pragma once

namespace Engine
{
  class Component
  {
  public:
    virtual ~Component() = default;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Update(float dt) = 0;
  };
}