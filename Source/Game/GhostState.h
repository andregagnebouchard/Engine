#pragma once
#include "MoveEvent.h" // For the direction
namespace Game
{
  struct GhostState {
    enum class Action {
      Respawning,
      Chasing,
      Fleeing
    };

    float positionX = 0.0f;
    float positionY = 0.0f;
    Action action = Action::Chasing;
    MoveEvent::Direction direction = MoveEvent::Direction::Up;
    int animationFrame = 0;
  };
}