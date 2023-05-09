#pragma once
namespace Game
{
  struct PacmanState {
    enum class Action {
      Idle,
      Moving,
      Eating,
      Dying
    };

    enum class MovingDirection {
      None,
      Up,
      Down,
      Left,
      Right
    };

    float positionX = 0.0f;
    float positionY = 0.0f;
    Action action = Action::Idle;
    MovingDirection direction = MovingDirection::None;
    int movingFrame = 0;
  };
}