#pragma once
#include <Engine\IGameLogicEvent.h>
using namespace Engine;
namespace Game
{
	class MoveEvent : public IGameLogicEvent
	{
	public:
		enum Direction
		{
			Up,
			Down,
			Left,
			Right
		};
		MoveEvent(float deltaX, float, float initialX, float initialY, Direction direction);
		~MoveEvent() = default;

		float GetInitialX() const { return m_InitialX; };
		float GetInitialY() const { return m_InitialY; };
		float GetDeltaX() const { return m_DeltaX; };
		float GetDeltaY() const { return m_DeltaY; };
		Direction GetDirection() const { return m_Direction; };
	private:
		float m_DeltaX;
		float m_DeltaY;
		float m_InitialX;
		float m_InitialY;
		Direction m_Direction;
	};
}