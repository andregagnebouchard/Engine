#pragma once
#include <Engine\IGameLogicEvent.h>
namespace Game
{
	class CollisionEvent: public IGameLogicEvent
	{
	public:
		CollisionEvent(int entityId1, int entityId2) : m_EntityId1(entityId1), m_EntityId2(entityId2) {};
		~CollisionEvent() = default;

		int GetEntityId1() const { return m_EntityId1; };
		int GetEntityId2() const { return m_EntityId2; };
	private:
		const int m_EntityId1;
		const int m_EntityId2;
	};
}