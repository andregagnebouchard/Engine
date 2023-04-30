#include "stdafx.h"
#include "MoveEvent.h"
using namespace Engine;
namespace Game
{
	MoveEvent::MoveEvent(float deltaX, float deltaY, float initialX, float initialY, Direction direction) :
		m_DeltaX(deltaX),
		m_DeltaY(deltaY),
		m_InitialX(initialX),
		m_InitialY(initialY),
		m_Direction(direction)
	{
	};
}