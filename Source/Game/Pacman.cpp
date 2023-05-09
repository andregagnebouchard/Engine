#include "stdafx.h"
#include "Pacman.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
#include "Entity.h"
#include "MoveEvent.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace Engine;
namespace Game
{
	PacmanInputMoveEvent::PacmanInputMoveEvent(Direction direction) : m_Direction(direction) {}
	//================================================Graphic==========================================================================================================
	PacmanGraphicComponent::PacmanGraphicComponent(int entityId, const PacmanState* state) :
		m_EntityId(entityId), 
		m_State(state)
	{
	};
	void PacmanGraphicComponent::Update(float dt)
	{
		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			PickSpriteName(),
			m_State->positionX,
			m_State->positionY));
	}

	wstring PacmanGraphicComponent::PickMovingSprite() const
	{
		if (m_State->direction == PacmanState::MovingDirection::Down)
		{
			if (m_State->movingFrame == 0)
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
	wstring PacmanGraphicComponent::PickDyingSprite() const
	{
		int animationSpriteId = m_State->movingFrame / PacmanConstants::framePerDyingAnimationSprite;
		wstringstream ss;
		ss << L"pacman_dying_" << animationSpriteId;
		return ss.str();
	}
	wstring PacmanGraphicComponent::PickSpriteName() const
	{
		if (m_State->action == PacmanState::Action::Moving)
			return PickMovingSprite();
		else if (m_State->action == PacmanState::Action::Dying)
			return PickDyingSprite();
		return L"pacman_right_0";
	}

	//================================================Input==========================================================================================================
	PacmanInputComponent::PacmanInputComponent(int entityId) : 
		m_EntityId(entityId) 
	{
	};

	void PacmanInputComponent::Shutdown()
	{
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_DOWN_PRESS)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_UP_PRESS)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_LEFT_PRESS)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_RIGHT_PRESS)));
	}



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
		PacmanInputMoveEvent::Direction inputDirection;
		if (direction == PacmanState::MovingDirection::Down)
			inputDirection = PacmanInputMoveEvent::Direction::Down;
		else if (direction == PacmanState::MovingDirection::Up)
			inputDirection = PacmanInputMoveEvent::Direction::Up;
		else if (direction == PacmanState::MovingDirection::Right)
			inputDirection = PacmanInputMoveEvent::Direction::Right;
		else if (direction == PacmanState::MovingDirection::Left)
			inputDirection = PacmanInputMoveEvent::Direction::Left;

		return make_shared<LogicEvent>(
			Event::Key
			(
				static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
				static_cast<int>(GameEventId::PacmanMoveInput),
				m_EntityId
			),
			make_shared<PacmanInputMoveEvent>(inputDirection)
			);
	}
	//================================================Logic==========================================================================================================
	PacmanLogicComponent::PacmanLogicComponent(int entityId, PacmanState *state, WorldGrid* worldGrid, const unordered_map<int, Entity::Type>* entityIdToEntityType) :
		m_EntityId(entityId), 
		m_State(state),
		m_WorldGrid(worldGrid),
		m_EntityIdToEntityType(entityIdToEntityType)
	{
	};

	void PacmanLogicComponent::Shutdown()
	{
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::GhostKillPacman)));
	}

	void PacmanLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::GhostKillPacman)));
	}

	void PacmanLogicComponent::Update(float dt)
	{
		if (m_State->action == PacmanState::Action::Dying)
			UpdateDyingLogic();
		else // Ignore all events if we're dying, they're irrelevant now
			ProcessEvents();
	}

	void PacmanLogicComponent::ProcessEvents()
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::PacmanMoveInput:
				TryMove(dynamic_pointer_cast<PacmanInputMoveEvent>(ev->GetGameLogicEvent()));
				break;
			case GameEventId::PauseGame:
				Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
				break;
			case GameEventId::UnpauseGame:
				Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
				break;
			case GameEventId::GhostKillPacman:
				m_State->action = PacmanState::Action::Dying;
				m_State->movingFrame = 0;
				// Stop processing inputs when we die
				// Potential bug - What if we process in the same frame as we die? Then we'll move first, then die. Might want to introduce the concept of priority events, or undo previous ones
				Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
			}
		}
	}

	void PacmanLogicComponent::UpdateDyingLogic()
	{
		if(m_State->movingFrame < PacmanConstants::dyingAnimationLength)
			m_State->movingFrame++;
		if(m_State->movingFrame >= PacmanConstants::dyingAnimationLength)
			Messager::Fire(make_shared<LogicEvent>
				(
					Event::Key
					(
						static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
						static_cast<int>(GameEventId::PacmanFinishesDyingAnimation),
						m_EntityId
					),
					nullptr
					));
	}

	void PacmanLogicComponent::TryMove(shared_ptr<PacmanInputMoveEvent> ev) // Should split that function
	{
		const PacmanInputMoveEvent::Direction moveDirection = ev->GetDirection();
		float deltaX = 0.0f;
		float deltaY = 0.0f;
		if (moveDirection == PacmanInputMoveEvent::Direction::Down)
			deltaY = PacmanConstants::moveDistanceByFrame;
		else if (moveDirection == PacmanInputMoveEvent::Direction::Up)
			deltaY = -PacmanConstants::moveDistanceByFrame;
		else if (moveDirection == PacmanInputMoveEvent::Direction::Right)
			deltaX = PacmanConstants::moveDistanceByFrame;
		else if (moveDirection == PacmanInputMoveEvent::Direction::Left)
			deltaX = -PacmanConstants::moveDistanceByFrame;

		const CellLocation newLocation = m_WorldGrid->GetCellLocationFromPosition(m_State->positionX + deltaX, m_State->positionY + deltaY);
		if (!m_WorldGrid->IsCellInbound(newLocation)) { // Don't move if new location is not inbound
			StopMoving();
			return;
		}

		int valueAtNewLocation = m_WorldGrid->GetCellValue(newLocation);
		if (valueAtNewLocation != WorldGrid::EmptyGridValue)
		{
			Entity::Type typeInNewLocation = m_EntityIdToEntityType->at(valueAtNewLocation);
			if (typeInNewLocation == Entity::Type::Wall) {
				StopMoving();
				return;
			}
		}

		// Move
		if (m_State->action != PacmanState::Action::Moving)
		{
			m_State->action = PacmanState::Action::Moving;
			m_State->movingFrame = 1;
		}
		else 
		{
			m_State->movingFrame++;
			if (m_State->movingFrame > 3)
				m_State->movingFrame = 0;
		}
		MoveEvent::Direction moveEventDirection;
		if (moveDirection == PacmanInputMoveEvent::Direction::Up) {
			m_State->direction = PacmanState::MovingDirection::Up;
			moveEventDirection = MoveEvent::Direction::Up;
		} else  if (moveDirection == PacmanInputMoveEvent::Direction::Down) {
			m_State->direction = PacmanState::MovingDirection::Down;
			moveEventDirection = MoveEvent::Direction::Down;
		} else  if (moveDirection == PacmanInputMoveEvent::Direction::Right) {
			m_State->direction = PacmanState::MovingDirection::Right;
			moveEventDirection = MoveEvent::Direction::Right;
		} else if (moveDirection == PacmanInputMoveEvent::Direction::Left) {
			m_State->direction = PacmanState::MovingDirection::Left;
			moveEventDirection = MoveEvent::Direction::Left;
		}

		float initialX = m_State->positionX;
		float initialY = m_State->positionY;

		m_State->positionX += deltaX;
		m_State->positionY += deltaY;

		Messager::Fire(make_shared<LogicEvent>
			(
				Event::Key
				(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::Move),
					m_EntityId
				),
				make_shared<MoveEvent>(deltaX, deltaY, initialX, initialY, moveEventDirection)
			));
	}

	void PacmanLogicComponent::StopMoving()
	{
		m_State->action = PacmanState::Action::Idle;
		m_State->movingFrame = 0;
	}
	//================================================Audio==========================================================================================================
	PacmanAudioComponent::PacmanAudioComponent(int entityId) : 
		m_EntityId(entityId) 
	{
	};

	void PacmanAudioComponent::Shutdown()
	{
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), m_EntityId));
	}

	void PacmanAudioComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), m_EntityId));
	}

	void PacmanAudioComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::Move:
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