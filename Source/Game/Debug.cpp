#include "stdafx.h"
#include "Debug.h"
#include "GameEventIds.h"
#include "DebugState.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	DebugInputComponent::DebugInputComponent(int entityId) :
		m_EntityId(entityId)
	{
	};

	void DebugInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_O_PRESS)));
	}

	void DebugInputComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Input)
				throw invalid_argument("A non-input event was caught by an input component");

			Messager::Fire(make_shared<LogicEvent>(
				Event::Key(
					static_cast<int>(EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::ToggleDebugModeInput),
					m_EntityId
				),
				nullptr)); // No payload for toggling debug menu

		}
	}

	DebugLogicComponent::DebugLogicComponent(int entityId, DebugState* state) :
		m_EntityId(entityId),
		m_State(state)
	{
	};

	void DebugLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::ToggleDebugModeInput)));
	}

	void DebugLogicComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Logic)
				throw invalid_argument("A non-logic event was caught by a logic component");

			if (m_State->isDebugModeActive)
			{
				m_State->isDebugModeActive = false;
			}
			else
			{
				m_State->isDebugModeActive = true;
			}
		}
	}
}