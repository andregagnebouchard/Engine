#pragma once
#include "Direction.h"
namespace Game
{
  struct GhostState {
    enum class Action {
      Respawning,
      Chasing,
      Fleeing,
      WaitingForPacmanDying // This happens when pacman dies, there is a second or so where all ghost stop moving
    };

    float positionX = 0.0f;
    float positionY = 0.0f;
    Action action = Action::Chasing;
    Direction direction = Direction::Up;
    int animationFrame = 0;
  };
}