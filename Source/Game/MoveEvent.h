#pragma once
#include <Engine\IGameLogicEvent.h>
#include "Direction.h"
using namespace Engine;
namespace Game
{
	class MoveEvent : public IGameLogicEvent
	{
	public:
		MoveEvent(float deltaX, float, float initialX, float initialY, Direction direction);
		~MoveEvent() = default;

		float GetInitialX() const { return m_InitialX; };
		float GetInitialY() const { return m_InitialY; };
		float GetDeltaX() const { return m_DeltaX; };
		float GetDeltaY() const { return m_DeltaY; };
		Direction GetDirection() const { return m_Direction; };
	private:
		const float m_DeltaX;
		const float m_DeltaY;
		const float m_InitialX;
		const float m_InitialY;
		const Direction m_Direction;
	};
}