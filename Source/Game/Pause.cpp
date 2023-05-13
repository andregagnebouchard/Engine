#include "stdafx.h"
#include "Pause.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	PauseGraphicComponent::PauseGraphicComponent(int entityId, const PauseState *state) :
		m_EntityId(entityId),
		m_State(state)
	{
	}

	void PauseGraphicComponent::Update()
	{
		if(m_State->isPaused)
			Messager::Fire(make_shared<RenderSpriteEvent>(
				Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
				L"pause_ui_element",
				250.0f,
				250.0f));
	}

	PauseInputComponent::PauseInputComponent(int entityId) :
		m_EntityId(entityId)
	{
	}

	void PauseInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_P_PRESS)));
	}

	void PauseInputComponent::Update()
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

	PauseLogicComponent::PauseLogicComponent(int entityId, PauseState *state) :
		m_EntityId(entityId),
		m_PauseState(state)
	{
	}

	void PauseLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PressedPauseButton), m_EntityId));
	}



	void PauseLogicComponent::Update()
	{
		while (!m_MsgQueue.Empty()) 
		{
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Logic)
				throw invalid_argument("A non-logic event was caught by a logic component");

			// Not checking the event content, we know it's a pause press
			if (m_PauseState->isPaused == false)
			{
				m_PauseState->isPaused = true;
				Messager::Fire(make_shared<LogicEvent>(Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)), nullptr));
			}
			else
			{
				m_PauseState->isPaused = false;
				Messager::Fire(make_shared<LogicEvent>(Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)), nullptr));
			}
		}
	}
}