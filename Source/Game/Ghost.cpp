#include "stdafx.h"
#include "Ghost.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
#include "EntityTypes.h"
#include "MoveEvent.h"
using namespace Engine;
namespace Game
{
	//================================================Graphic==========================================================================================================
	GhostGraphicComponent::GhostGraphicComponent(int entityId, const GhostState* state, GhostType type) :
		m_EntityId(entityId),
		m_State(state),
		m_Type(type)
	{
	}

	void GhostGraphicComponent::Update()
	{
		if (m_State->action == GhostState::Action::Chasing || m_State->action == GhostState::Action::WaitingForPacmanDying)
			ChasingUpdate();
		else if (m_State->action == GhostState::Action::Fleeing)
			FleeingUpdate();
		else if (m_State->action == GhostState::Action::Respawning)
			RespawningUpdate();
	}

	void GhostGraphicComponent::ChasingUpdate() const
	{
		wstring spriteName = L"";
		const bool wobbling = m_State->animationFrame < GhostConstants::chasingFramePerWobbling;
		if (m_State->direction == Direction::Down)
		{
			if (wobbling)
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_down_0";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_down_0";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_down_0";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_down_0";
			}
			else
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_down_1";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_down_1";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_down_1";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_down_1";
			}
		}
		else if (m_State->direction == Direction::Up)
		{
			if (wobbling)
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_up_0";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_up_0";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_up_0";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_up_0";
			}
			else
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_up_1";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_up_1";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_up_1";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_up_1";
			}
		}
		else if (m_State->direction == Direction::Left)
		{
			if (wobbling)
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_left_0";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_left_0";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_left_0";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_left_0";
			}
			else
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_left_1";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_left_1";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_left_1";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_left_1";
			}
		}
		else if (m_State->direction == Direction::Right)
		{
			if (wobbling)
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_right_0";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_right_0";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_right_0";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_right_0";
			}
			else
			{
				if (m_Type == GhostType::Blue)
					spriteName = L"ghost_blue_right_1";
				else if (m_Type == GhostType::Red)
					spriteName = L"ghost_red_right_1";
				else if (m_Type == GhostType::Pink)
					spriteName = L"ghost_pink_right_1";
				else if (m_Type == GhostType::Orange)
					spriteName = L"ghost_orange_right_1";
			}
		}

		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			spriteName,
			m_State->positionX,
			m_State->positionY));
	}

	void GhostGraphicComponent::FleeingUpdate() const
	{
		wstring spriteName = L"";
		const bool wobbling = m_State->animationFrame % (2 * GhostConstants::fleeingFramePerWobling) < GhostConstants::fleeingFramePerWobling;
		// You are white for the first X frames, then every Y frames
		if (m_State->animationFrame >= GhostConstants::fleeingFrameBeforeFirstFlash 
			&& m_State->animationFrame % (2 * GhostConstants::fleeingFlashFrameDuration) < GhostConstants::fleeingFlashFrameDuration)
		{
			if (wobbling)
				spriteName = L"ghost_fleeing_white_0";
			else
				spriteName = L"ghost_fleeing_white_1";
		}
		// If you are not white, then you are blue
		else
		{
			if(wobbling)
				spriteName = L"ghost_fleeing_blue_0";
			else
				spriteName = L"ghost_fleeing_blue_1";
		}
		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			spriteName,
			m_State->positionX,
			m_State->positionY));
	}

	void GhostGraphicComponent::RespawningUpdate() const
	{
		// The little eyes going back to the cage
		wstring spriteName = L"";
		if (m_State->direction == Direction::Down)
			spriteName = L"ghost_respawning_down";
		else if (m_State->direction == Direction::Up)
			spriteName = L"ghost_respawning_up";
		else if (m_State->direction == Direction::Left)
			spriteName = L"ghost_respawning_left";
		else if (m_State->direction == Direction::Right)
			spriteName = L"ghost_respawning_right";

		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			spriteName,
			m_State->positionX,
			m_State->positionY));
	}

	//================================================Logic==========================================================================================================
	GhostLogicComponent::GhostLogicComponent(int entityId, GhostState* state, const Engine::Grid* worldGrid, const unordered_map<int, EntityType>* entityIdToEntityType, const IGhostMovementBehaviour* movementBehaviour) :
		m_EntityId(entityId),
		m_State(state),
		m_WorldGrid(worldGrid),
		m_EntityIdToEntityType(entityIdToEntityType),
		m_MovementBehaviour(movementBehaviour),
		m_EventCallback(bind(&GhostLogicComponent::OnEvent, this, placeholders::_1))
	{
	}

	void GhostLogicComponent::Init()
	{
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::BigDotEaten)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanEatGhost), m_EntityId));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::GhostTouchesPacman)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanStartDyingAnimation)));
	}

	void GhostLogicComponent::Shutdown()
	{
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::BigDotEaten)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanEatGhost), m_EntityId));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::GhostTouchesPacman)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanStartDyingAnimation)));
	}

	void GhostLogicComponent::OnEvent(const shared_ptr<Event> event)
	{
		// Process event right away. This is to be in the correct state before
		// ghost's tick update, in case an event already modified its state
		const auto ev = dynamic_pointer_cast<LogicEvent>(event);
		switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
		{
		case GameEventId::BigDotEaten:
			m_State->action = GhostState::Action::Fleeing;
			m_State->animationFrame = 0;
			break;
		case GameEventId::PacmanEatGhost:
			m_State->action = GhostState::Action::Respawning;
			m_State->animationFrame = 0;
			break;
		case GameEventId::GhostTouchesPacman:
			m_State->action = GhostState::Action::WaitingForPacmanDying;
			m_State->animationFrame = 0;
			break;
		case GameEventId::PacmanStartDyingAnimation: // Ghost disapears when pacman dies
			KillYourself();
		}
	}

	void GhostLogicComponent::Update()
	{
		if (m_State->action == GhostState::Action::Chasing)
			ChasingLogicUpdate();
		else if (m_State->action == GhostState::Action::Fleeing)
			FleeingLogicUpdate();
		else if (m_State->action == GhostState::Action::Respawning)
			RespawningLogicUpdate();
		else if (m_State->action == GhostState::Action::WaitingForPacmanDying)
			WaitingForPacmanDyingLogicUpdate();
	}

	void GhostLogicComponent::KillYourself()
	{
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), Engine::EntityEvent::Type::Delete, L"Ghost", m_EntityId, nullptr));
	}

	void GhostLogicComponent::WaitingForPacmanDyingLogicUpdate()
	{
		// Toggle the blobbing
		if (m_State->animationFrame < 2 * GhostConstants::chasingFramePerWobbling) // There are 2 frames in the animation
			m_State->animationFrame++;
		else
			m_State->animationFrame = 0;
	}

	void GhostLogicComponent::ChasingLogicUpdate()
	{
		const Engine::Grid::CellLocation currentLocation = m_WorldGrid->GetCellLocationFromPosition(m_State->positionX, m_State->positionY);
		const Engine::Grid::CellLocation targetLocation = m_MovementBehaviour->ChooseNextCellToMove();
		float deltaX = 0;
		float deltaY = 0;
		const float initialX = m_State->positionX;
		const float initialY = m_State->positionY;

		// New location will never be the same as current location, so we can determine the direction by the target
		// The movement behaviour class always choose a valid location for the frame, so no checks required. Just move
		if (targetLocation.col < currentLocation.col)
		{
			m_State->direction = Direction::Left;
			deltaX -= GhostConstants::moveDistanceByFrame;
		}
		else if (targetLocation.col > currentLocation.col)
		{
			m_State->direction = Direction::Right;
			deltaX += GhostConstants::moveDistanceByFrame;
		}
		else if (targetLocation.row > currentLocation.row)
		{
			m_State->direction = Direction::Down;
			deltaY = GhostConstants::moveDistanceByFrame;
		}
		else if (targetLocation.row < currentLocation.row)
		{
			m_State->direction = Direction::Up;
			deltaY -= GhostConstants::moveDistanceByFrame;
		}

		m_State->positionX += deltaX;
		m_State->positionY += deltaY;

		// Toggle the blobbing
		if (m_State->animationFrame < 2*GhostConstants::chasingFramePerWobbling) // There are 2 frames in the animation
			m_State->animationFrame++;
		else
			m_State->animationFrame = 0;

		// Tell the world the ghost moved
		// Disabled for testing
		/*
		Messager::Fire(make_shared<LogicEvent>
			(
				Event::Key
				(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::Move),
					m_EntityId
				),
				make_shared<MoveEvent>(deltaX, deltaY, initialX, initialY, m_State->direction)
				));
				*/
	}

	void GhostLogicComponent::FleeingLogicUpdate()
	{
		m_State->animationFrame++;
		if (m_State->animationFrame > GhostConstants::fleeingEnd)
		{
			m_State->action = GhostState::Action::Chasing;
			m_State->animationFrame = 0;
		}
	}

	void GhostLogicComponent::RespawningLogicUpdate()
	{
		m_State->animationFrame++;

		// We should actually top when it reaches the cage, but movement is not implemented yet, so just delaying for now
		if (m_State->animationFrame > GhostConstants::fleeingEnd)
		{
			m_State->action = GhostState::Action::Chasing;
			m_State->animationFrame = 0;
		}
	}
}