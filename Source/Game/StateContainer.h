#pragma once
#include <Engine/PackedArray.h>
#include "PacmanState.h"
#include "PauseState.h"
#include "SmallDotState.h"
#include "BigDotState.h"
#include "DebugState.h"
#include "GhostState.h"
using namespace std;
using namespace Engine;
namespace Game
{
	// Contains the state of all the objects in the game
	struct StateContainer
	{
		PacmanState pacmanState;
		PauseState pauseState;
		PackedArray<SmallDotState, 1024> smallDotStates; // There are 240 small dots in the base game, but increasing for testing
		PackedArray<BigDotState, 32> bigDotStates; // There are 4 small dots in the base game, but increasing for testing
		DebugState debugState;
		GhostState blueGhostState;
		GhostState redGhostState;
		GhostState pinkGhostState;
		GhostState orangeGhostState;
	};
}
