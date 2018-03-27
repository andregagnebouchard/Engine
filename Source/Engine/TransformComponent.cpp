#include "stdafx.h"
#include <Engine/TransformComponent.h>

namespace Engine
{
  shared_ptr<TransformComponent> TransformComponent::Create(float x, float y)
  {
    return make_shared<TransformComponent>(x, y);
  }

  TransformComponent::TransformComponent(float x, float y) :
  m_X(x),
  m_Y(y)
  {
  }

  void TransformComponent::Init()
  {
    
  }
  void TransformComponent::Shutdown()
  {
    
  }
  void TransformComponent::Update(float dt)
  {
    
  }
}