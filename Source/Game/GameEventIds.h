#pragma once
#include "stdafx.h"
namespace Game
{
	enum class GameEventId
	{
		PacmanMoveInput,
		Move,
		PressedPauseButton,
		PauseGame,
		UnpauseGame,
		Collision,
		ToggleDebugModeInput,
		BigDotEaten,
		PacmanEatGhost,
		GhostTouchesPacman,
		PacmanStartDyingAnimation
	};
}