#pragma once
#include "Direction.h"
namespace Game
{
  struct PacmanState {
    enum class Action {
      Idle,
      Moving,
      Eating,
      WaitingToDie, // In-between touching a ghost, and dying animation
      Dying
    };

    float positionX = 0.0f;
    float positionY = 0.0f;
    Action action = Action::Idle;
    Direction direction = Direction::None;
    int movingFrame = 0;
  };
}