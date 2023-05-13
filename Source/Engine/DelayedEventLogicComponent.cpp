#include "stdafx.h"
#include "Messager.h"
#include "EventDefinition.h"
#include "DelayedEventLogicComponent.h"

namespace Engine
{
	DelayedEventLogicComponent::DelayedEventLogicComponent(int entityId, int delayTick, const Event::Key& keyToEmit) :
		m_EntityId(entityId),
		m_DelayTick(delayTick),
		m_KeyToEmit(keyToEmit),
		m_TickCounter(0)
	{
	}

	void DelayedEventLogicComponent::Update()
	{
		m_TickCounter++;
		if (m_TickCounter >= m_DelayTick)
		{
			// Fire the event
			Engine::Messager::Fire(
				make_shared<Engine::LogicEvent>(
					m_KeyToEmit, nullptr));

			// Destroy yourself
			Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), Engine::EntityEvent::Type::Delete, L"DelayedEvent", m_EntityId, nullptr));
		}
	}
}