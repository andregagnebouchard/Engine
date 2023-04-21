#include "stdafx.h"
#include "Pause.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	PauseInputComponent::PauseInputComponent(int entityId) :
		m_EntityId(entityId)
	{
	}

	void PauseInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_P_PRESS)));
	}

	void PauseInputComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Input)
				throw invalid_argument("A non-input event was caught by an input component");

			Messager::Fire(make_shared<LogicEvent>(
				Event::Key(
					static_cast<int>(EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::PressedPauseButton),
					m_EntityId
				), 
				nullptr)); // No payload for pause
		}
	}

	PauseLogicComponent::PauseLogicComponent(int entityId) :
		m_EntityId(entityId)
	{
	}

	void PauseLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PressedPauseButton), m_EntityId));
	}



	void PauseLogicComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Logic)
				throw invalid_argument("A non-logic event was caught by a logic component");

			if (m_PauseState.isPaused == false)
			{
				m_PauseState.isPaused = true;
				Messager::Fire(make_shared<LogicEvent>(Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)), nullptr));
			}
			else
			{
				m_PauseState.isPaused = false;
				Messager::Fire(make_shared<LogicEvent>(Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)), nullptr));
			}
		}
	}
}