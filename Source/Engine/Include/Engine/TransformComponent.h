#pragma once
#include <Engine\Component.h>
#include <Engine\Typedef.h>
#include <Engine\Component.h>
#include <memory>
using namespace std;
namespace Engine
{
  class TransformComponent : public Component
  {
  public:
    static shared_ptr<TransformComponent> Create(float x, float y);
    ~TransformComponent() = default;

    void Init() override;
    void Shutdown() override;
    void Update(float dt) override;

  private:
    TransformComponent(float x, float y);
    float m_X;
    float m_Y;
  };
}