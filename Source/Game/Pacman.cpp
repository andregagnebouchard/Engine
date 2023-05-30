#include "stdafx.h"
#include "Pacman.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
#include "EntityTypes.h"
#include "MoveEvent.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace Engine;
namespace Game
{
	PacmanInputMoveEvent::PacmanInputMoveEvent(const Direction direction) : m_Direction(direction) {}
	//================================================Graphic==========================================================================================================
	PacmanGraphicComponent::PacmanGraphicComponent(int entityId, const PacmanState* state) :
		m_EntityId(entityId), 
		m_State(state)
	{
	};
	void PacmanGraphicComponent::Update()
	{
		// Send the right sprite at our position
		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			PickSpriteName(),
			m_State->positionX,
			m_State->positionY));
	}

	wstring PacmanGraphicComponent::PickMovingSprite() const
	{
		if (m_State->direction == Direction::Down)
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
		if (m_State->direction == Direction::Up)
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
		if (m_State->direction == Direction::Left)
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
		if (m_State->direction == Direction::Right)
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
		return L"";
	}
	wstring PacmanGraphicComponent::PickDyingSprite() const
	{
		int animationSpriteId = m_State->movingFrame / PacmanConstants::framePerDyingAnimationSprite;

		// Graphic component is updated in the frame pacman dies, before it dies. So keep the last sprite when that happens
		if (animationSpriteId >= PacmanConstants::dyingAnimationSpriteQuantity)
			animationSpriteId = PacmanConstants::dyingAnimationSpriteQuantity - 1;
		wstringstream ss;
		ss << L"pacman_dying_" << animationSpriteId; // This is to avoid ~11 if/else branches to choose the suffix sprite number
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
		m_EntityId(entityId),
		m_EventCallback(bind(&PacmanInputComponent::OnEvent, this, placeholders::_1))
	{
	};

	void PacmanInputComponent::Shutdown()
	{
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_DOWN_PRESS)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_UP_PRESS)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_LEFT_PRESS)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_RIGHT_PRESS)));
	}

	void PacmanInputComponent::Init()
	{
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_DOWN_PRESS)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_UP_PRESS)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_LEFT_PRESS)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::KEY_RIGHT_PRESS)));
	}

	void PacmanInputComponent::OnEvent(const shared_ptr<Event> event)
	{
		// We buffer the input event, as we only want to process input
		// once per tick
		m_MsgQueue.push(event);
	}
	void PacmanInputComponent::Update()
	{
		while (!m_MsgQueue.empty()) {
			const shared_ptr<Event> event = m_MsgQueue.front();
			m_MsgQueue.pop();
			if (event->GetType() != Event::Type::Input)
				throw invalid_argument("A non-input event was caught by an input component");

			const auto ev = dynamic_pointer_cast<InputEvent>(event);
			switch (ev->GetKey().first)
			{
				case static_cast<int>(Engine::EventDefinition::Id::KEY_DOWN_PRESS) :
					Messager::Fire(CreateMoveEvent(Direction::Down));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_UP_PRESS) :
					Messager::Fire(CreateMoveEvent(Direction::Up));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_LEFT_PRESS) :
					Messager::Fire(CreateMoveEvent(Direction::Left));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_RIGHT_PRESS) :
					Messager::Fire(CreateMoveEvent(Direction::Right));
					break;
			}
		}
	}

	shared_ptr<LogicEvent> PacmanInputComponent::CreateMoveEvent(Direction direction)
	{
		return make_shared<LogicEvent>(
			Event::Key
			(
				static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
				static_cast<int>(GameEventId::PacmanMoveInput),
				m_EntityId
			),
			make_shared<PacmanInputMoveEvent>(direction)
			);
	}
	//================================================Logic==========================================================================================================
	PacmanLogicComponent::PacmanLogicComponent(int entityId, PacmanState *state, Engine::Grid* worldGrid, const unordered_map<int, EntityType>* entityIdToEntityType) :
		m_EntityId(entityId), 
		m_State(state),
		m_WorldGrid(worldGrid),
		m_EntityIdToEntityType(entityIdToEntityType),
		m_EventCallback(bind(&PacmanLogicComponent::OnEvent, this, placeholders::_1))
	{
	};

	void PacmanLogicComponent::Shutdown()
	{
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::GhostTouchesPacman)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanStartDyingAnimation)));
	}

	void PacmanLogicComponent::Init()
	{
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PauseGame)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::UnpauseGame)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::GhostTouchesPacman)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanStartDyingAnimation)));
	}

	void PacmanLogicComponent::OnEvent(const shared_ptr<Event> event)
	{
		// Process event right away. This is to be in the correct state before
		// pacman's tick update, in case an event already modified its state
		const auto ev = dynamic_pointer_cast<LogicEvent>(event);
		switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
		{
		case GameEventId::PacmanMoveInput:
			if(m_State->action != PacmanState::Action::Dying && m_State->action != PacmanState::Action::WaitingToDie) // Don't move if we're dead
				TryMove(dynamic_pointer_cast<PacmanInputMoveEvent>(ev->GetGameLogicEvent())); // Might fail moving if it's out of bound
			break;
		case GameEventId::PauseGame:
			Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
			break;
		case GameEventId::UnpauseGame:
			Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanMoveInput), m_EntityId));
			break;
		case GameEventId::GhostTouchesPacman:
			m_State->action = PacmanState::Action::WaitingToDie; 
			m_State->movingFrame = 0;
			break;
		case GameEventId::PacmanStartDyingAnimation:
			m_State->action = PacmanState::Action::Dying;
			m_State->movingFrame = 0;
		}
	}
	void PacmanLogicComponent::Update()
	{
		// Most updates are results of event, except dying
		if (m_State->action == PacmanState::Action::Dying)
			UpdateDying();
	}

	void PacmanLogicComponent::UpdateDying()
	{
		if(m_State->movingFrame < PacmanConstants::dyingAnimationLength)
			m_State->movingFrame++;
		if(m_State->movingFrame >= PacmanConstants::dyingAnimationLength) // Kill yourself when you reach the end of the animation
			Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), Engine::EntityEvent::Type::Delete, L"Pacman", m_EntityId, nullptr));
	}

	void PacmanLogicComponent::TryMove(const shared_ptr<PacmanInputMoveEvent> ev)
	{
		const Direction moveDirection = ev->GetDirection();
		const float deltaX = FindDeltaX(moveDirection);
		const float deltaY = FindDeltaY(moveDirection);

		const Engine::Grid::CellLocation newLocation = m_WorldGrid->GetCellLocationFromPosition(m_State->positionX + deltaX, m_State->positionY + deltaY);
		if (!m_WorldGrid->IsCellInbound(newLocation)) // Don't move if new location is not inbound
			return StopMoving();

		const int valueAtNewLocation = m_WorldGrid->GetCellValue(newLocation);
		if (valueAtNewLocation != Engine::Grid::EmptyGridValue && m_EntityIdToEntityType->at(valueAtNewLocation) == EntityType::Wall)
				return StopMoving();

		m_State->action != PacmanState::Action::Moving ? IdleToMove() : KeepMoving();
		const float initialX = m_State->positionX;
		const float initialY = m_State->positionY;

		// Update state
		m_State->direction = moveDirection;
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
				make_shared<MoveEvent>(deltaX, deltaY, initialX, initialY, moveDirection)
				));
	}

	float PacmanLogicComponent::FindDeltaX(Direction direction) const
	{
		if (direction == Direction::Right)
			return PacmanConstants::moveDistanceByFrame;
		else if (direction == Direction::Left)
			return -PacmanConstants::moveDistanceByFrame;
		return 0.0f;
	}
	float PacmanLogicComponent::FindDeltaY(Direction direction) const
	{
		if (direction == Direction::Up)
			return -PacmanConstants::moveDistanceByFrame;
		else if (direction == Direction::Down)
			return PacmanConstants::moveDistanceByFrame;
		return 0.0f;
	}
	void PacmanLogicComponent::KeepMoving()
	{
		m_State->movingFrame++;
		if (m_State->movingFrame > 3) // Reset to closed mouth sprite if we reach the end
			m_State->movingFrame = 0;
	}
	void PacmanLogicComponent::IdleToMove()
	{
		m_State->action = PacmanState::Action::Moving;
		m_State->movingFrame = 1; // Frame where pacman opens the mouth
	}

	void PacmanLogicComponent::StopMoving()
	{
		m_State->action = PacmanState::Action::Idle;
		m_State->movingFrame = 0;
	}
	//================================================Audio==========================================================================================================
	PacmanAudioComponent::PacmanAudioComponent(int entityId) : 
		m_EntityId(entityId),
		m_EventCallback(bind(&PacmanAudioComponent::OnEvent, this, placeholders::_1))
	{
	};

	void PacmanAudioComponent::Shutdown()
	{
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), m_EntityId));
	}

	void PacmanAudioComponent::Init()
	{
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), m_EntityId));
	}

	void PacmanAudioComponent::OnEvent(const shared_ptr<Engine::Event> event)
	{
		const auto ev = dynamic_pointer_cast<LogicEvent>(event);
		switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
		{
		case GameEventId::Move:
			Messager::Fire(CreateAudioEvent());
			break;
		}
	}

	shared_ptr<AudioEvent> PacmanAudioComponent::CreateAudioEvent() const
	{
		const Event::Key key(static_cast<int>(Engine::EventDefinition::Id::AUDIO));
		return make_shared<AudioEvent>(key, L"pacman_chomp");
	}
}