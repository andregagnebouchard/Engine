#pragma once
#include <Engine/PackedArray.h>
#include "PacmanState.h"
#include "PauseState.h"
#include "DotState.h"
#include "DebugState.h"
using namespace std;
using namespace Engine;
namespace Game
{
	struct StateContainer
	{
		PacmanState pacmanState;
		PauseState pauseState;
		PackedArray<SmallDotState, 1024> dotStates; // There are 240 small dots in the base game, but increasing for testing
		DebugState debugState;
	};
}
