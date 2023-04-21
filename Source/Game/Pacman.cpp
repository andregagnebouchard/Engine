#include "stdafx.h"
#include "Pacman.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	//================================================Graphic==========================================================================================================
	PacmanGraphicComponent::PacmanGraphicComponent(int entityId, shared_ptr<PacmanState> state) : 
		m_EntityId(entityId), 
		m_State(state) 
	{
	};
	void PacmanGraphicComponent::Update(float dt)
	{
		Messager::Fire(make_shared<RenderEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			PickSpriteName(),
			m_State->posX,
			m_State->posY));
	}

	wstring PacmanGraphicComponent::PickSpriteName() const
	{
		if (m_State->actionState == PacmanActionState::MOVING)
		{
			if (m_State->direction == PacmanMovingDirection::DOWN)
			{
				if(m_State->movingFrame == 0)
					return L"pacman_down_0";
				if (m_State->movingFrame == 1)
					return L"pacman_down_1";
				if (m_State->movingFrame == 2)
					return L"pacman_down_2";
				if (m_State->movingFrame == 3)
					return L"pacman_down_1";
			}
			if (m_State->direction == PacmanMovingDirection::UP)
			{
				if (m_State->movingFrame == 0)
					return L"pacman_up_0";
				if (m_State->movingFrame == 1)
					return L"pacman_up_1";
				if (m_State->movingFrame == 2)
					return L"pacman_up_2";
				if (m_State->movingFrame == 3)
					return L"pacman_up_1";
			}
			if (m_State->direction == PacmanMovingDirection::LEFT)
			{
				if (m_State->movingFrame == 0)
					return L"pacman_left_0";
				if (m_State->movingFrame == 1)
					return L"pacman_left_1";
				if (m_State->movingFrame == 2)
					return L"pacman_left_2";
				if (m_State->movingFrame == 3)
					return L"pacman_left_1";
			}
			if (m_State->direction == PacmanMovingDirection::RIGHT)
			{
				if (m_State->movingFrame == 0)
					return L"pacman_right_0";
				if (m_State->movingFrame == 1)
					return L"pacman_right_1";
				if (m_State->movingFrame == 2)
					return L"pacman_right_2";
				if (m_State->movingFrame == 3)
					return L"pacman_right_1";
			}
		}
		return L"pacman_right_0";
	}

	//================================================Input==========================================================================================================
	PacmanInputComponent::PacmanInputComponent(int entityId) : 
		m_EntityId(entityId) 
	{
	};

	void PacmanInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_DOWN_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_UP_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_LEFT_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_RIGHT_PRESS)));
	}

	void PacmanInputComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Input)
				throw invalid_argument("A non-input event was caught by an input component");

			auto ev = dynamic_pointer_cast<InputEvent>(event);
			Engine::Event::Key key = ev->GetKey();

			switch (key.first)
			{
				case static_cast<int>(Engine::EventDefinition::Id::KEY_DOWN_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanMovingDirection::DOWN));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_UP_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanMovingDirection::UP));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_LEFT_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanMovingDirection::LEFT));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_RIGHT_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanMovingDirection::RIGHT));
					break;
			}
		}
	}

	shared_ptr<LogicEvent> PacmanInputComponent::CreateMoveEvent(PacmanMovingDirection direction)
	{
		int deltaX = 0;
		int deltaY = 0;
		switch (direction)
		{
		case PacmanMovingDirection::DOWN:
			deltaY = 10;
			break;
		case PacmanMovingDirection::UP:
			deltaY = -10;
			break;
		case PacmanMovingDirection::LEFT:
			deltaX = -10;
			break;
		case PacmanMovingDirection::RIGHT:
			deltaX = 10;
			break;
		}
		return make_shared<LogicEvent>(
			Event::Key
			(
				static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
				static_cast<int>(GameEventId::PacmanMove),
				m_EntityId
			),
			make_shared<MovePacmanLogicEvent>(deltaX, deltaY, direction)
			);
	}
	//================================================Logic==========================================================================================================
	PacmanLogicComponent::PacmanLogicComponent(int entityId, shared_ptr<PacmanState> state) : 
		m_EntityId(entityId), 
		m_State(state) 
	{
	};

	MovePacmanLogicEvent::MovePacmanLogicEvent(int deltaX, int deltaY, PacmanMovingDirection direction) : 
		m_DeltaX(deltaX),
		m_DeltaY(deltaY),
		m_Direction(direction)
	{
	};

	void PacmanLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMove), m_EntityId));
	}

	void PacmanLogicComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::PacmanMove:
				Move(dynamic_pointer_cast<MovePacmanLogicEvent>(ev->GetGameLogicEvent()));
				break;
			}
		}
	}

	void PacmanLogicComponent::Move(shared_ptr<MovePacmanLogicEvent> ev)
	{
		if (m_State->actionState != PacmanActionState::MOVING)
		{
			m_State->actionState = PacmanActionState::MOVING;
			m_State->movingFrame = 1;
		}
		else {
			m_State->movingFrame++;
			if (m_State->movingFrame > 3)
				m_State->movingFrame = 0;
		}

		if (ev->GetDirection() != m_State->direction)
		{
			m_State->direction = ev->GetDirection();
		}


		m_State->posX += ev->GetDeltaX();
		m_State->posY += ev->GetDeltaY();
	}
	//================================================Audio==========================================================================================================
	PacmanAudioComponent::PacmanAudioComponent(int entityId) : 
		m_EntityId(entityId) 
	{
	};
	void PacmanAudioComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMove), m_EntityId));
	}

	void PacmanAudioComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::PacmanMove:
				Messager::Fire(CreateAudioEvent());
				break;
			}
		}
	}

	shared_ptr<AudioEvent> PacmanAudioComponent::CreateAudioEvent() const
	{
		Event::Key key(static_cast<int>(Engine::EventDefinition::Id::AUDIO));
		return make_shared<AudioEvent>(key, L"pacman_chomp");
	}
}