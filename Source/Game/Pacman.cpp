#include "stdafx.h"
#include "Pacman.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	//================================================Graphic==========================================================================================================
	PacmanGraphicComponent::PacmanGraphicComponent(int entityId, const PacmanState* state) :
		m_EntityId(entityId), 
		m_State(state)
	{
	};
	void PacmanGraphicComponent::Update(float dt)
	{
		Messager::Fire(make_shared<RenderEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			PickSpriteName(),
			m_State->positionX,
			m_State->positionY));
	}

	wstring PacmanGraphicComponent::PickSpriteName() const
	{
		if (m_State->action == PacmanState::Action::Moving)
		{
			if (m_State->direction == PacmanState::MovingDirection::Down)
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
			if (m_State->direction == PacmanState::MovingDirection::Up)
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
			if (m_State->direction == PacmanState::MovingDirection::Left)
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
			if (m_State->direction == PacmanState::MovingDirection::Right)
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
					Messager::Fire(CreateMoveEvent(PacmanState::MovingDirection::Down));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_UP_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanState::MovingDirection::Up));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_LEFT_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanState::MovingDirection::Left));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_RIGHT_PRESS) :
					Messager::Fire(CreateMoveEvent(PacmanState::MovingDirection::Right));
					break;
			}
		}
	}

	shared_ptr<LogicEvent> PacmanInputComponent::CreateMoveEvent(PacmanState::MovingDirection direction)
	{
		int deltaX = 0;
		int deltaY = 0;
		switch (direction)
		{
		case PacmanState::MovingDirection::Down:
			deltaY = 10;
			break;
		case PacmanState::MovingDirection::Up:
			deltaY = -10;
			break;
		case PacmanState::MovingDirection::Left:
			deltaX = -10;
			break;
		case PacmanState::MovingDirection::Right:
			deltaX = 10;
			break;
		}
		return make_shared<LogicEvent>(
			Event::Key
			(
				static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
				static_cast<int>(GameEventId::PacmanMoveInput),
				m_EntityId
			),
			make_shared<MovePacmanLogicEvent>(deltaX, deltaY, direction)
			);
	}
	//================================================Logic==========================================================================================================
	PacmanLogicComponent::PacmanLogicComponent(int entityId, PacmanState *state) :
		m_EntityId(entityId), 
		m_State(state)
	{
	};

	MovePacmanLogicEvent::MovePacmanLogicEvent(int deltaX, int deltaY, PacmanState::MovingDirection direction) : 
		m_DeltaX(deltaX),
		m_DeltaY(deltaY),
		m_Direction(direction)
	{
	};

	void PacmanLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)));
	}

	void PacmanLogicComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::PacmanMoveInput:
				Move(dynamic_pointer_cast<MovePacmanLogicEvent>(ev->GetGameLogicEvent()));
				break;
			case GameEventId::PauseGame:
				Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
				break;
			case GameEventId::UnpauseGame:
				Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
				break;
			}
		}
	}

	void PacmanLogicComponent::Move(shared_ptr<MovePacmanLogicEvent> ev)
	{
		if (m_State->action != PacmanState::Action::Moving)
		{
			m_State->action = PacmanState::Action::Moving;
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


		m_State->positionX += ev->GetDeltaX();
		m_State->positionY += ev->GetDeltaY();


		Messager::Fire(make_shared<LogicEvent>(
			Event::Key
			(
				static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
				static_cast<int>(GameEventId::PacmanMove),
				m_EntityId
			),
			nullptr
			));
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