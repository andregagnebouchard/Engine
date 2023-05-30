#include "stdafx.h"
#include <Engine\EventDefinition.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\EntityIdCounter.h>
#include "Collision.h"
#include "CollisionEvent.h"
#include "GameEventIds.h"
#include "StateContainer.h"
#include "EntityCreatedPayload.h"
#include <functional>
using namespace Engine;
namespace Game
{
	CollisionLogicComponent::CollisionLogicComponent(int entityId, StateContainer* stateContainer, const unordered_map<int, EntityType>* entityIdToType) :
		m_EntityId(entityId),
		m_Callback(bind(&CollisionLogicComponent::OnCollision, this, placeholders::_1)),
		m_StateContainer(stateContainer),
		m_EntityIdToType(entityIdToType)
	{
	};

	void CollisionLogicComponent::Init()
	{
		Messager::Attach(&m_Callback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Collision)));
	}

	void CollisionLogicComponent::OnCollision(const shared_ptr<Event> event)
	{
		if (event->GetType() != Event::Type::Logic)
			throw invalid_argument("CollisionLogicComponent received a non logic event");

		const auto ev = dynamic_pointer_cast<LogicEvent>(event);
		const auto collisionEvent = dynamic_pointer_cast<CollisionEvent>(ev->GetGameLogicEvent());
		const EntityType type1 = m_EntityIdToType->at(collisionEvent->GetEntityId1());
		const EntityType type2 = m_EntityIdToType->at(collisionEvent->GetEntityId2());
		const int id1 = collisionEvent->GetEntityId2();
		const int id2 = collisionEvent->GetEntityId2();
		if (type1 == EntityType::SmallDot && type2 == EntityType::Pacman)
			OnCollisionPacmanSmallDot(id2, id1);
		else if (type1 == EntityType::Pacman && type2 == EntityType::SmallDot)
			OnCollisionPacmanSmallDot(id1, id2);
		else if (type1 == EntityType::Pacman && type2 == EntityType::BigDot)
			OnCollisionPacmanBigDot(id1, id2);
		else if (type1 == EntityType::BigDot && type2 == EntityType::Pacman)
			OnCollisionPacmanSmallDot(id2, id1);
		else if (type1 == EntityType::BlueGhost && type2 == EntityType::Pacman)
			OnCollisionPacmanBlueGhost(id2, id1);
		else if (type1 == EntityType::Pacman && type2 == EntityType::BlueGhost)
			OnCollisionPacmanBlueGhost(id1, id2);
	}

	void CollisionLogicComponent::OnCollisionPacmanBlueGhost(int pacmanEntityId, int blueGhostEntityId)
	{
		if (m_StateContainer->blueGhostState.action == GhostState::Action::Fleeing)
			OnCollisionPacmanFleeingGhost(pacmanEntityId, blueGhostEntityId);
		else if (m_StateContainer->blueGhostState.action == GhostState::Action::Chasing)
			OnCollisionPacmanChasingGhost(pacmanEntityId, blueGhostEntityId);
	}

	void CollisionLogicComponent::OnCollisionPacmanFleeingGhost(int pacmanEntityId, int blueGhostEntityId)
	{
		Engine::Messager::Fire(
			make_shared<Engine::LogicEvent>(
				Engine::Event::Key(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::PacmanEatGhost),
					blueGhostEntityId
				),
				nullptr));
	}
	void CollisionLogicComponent::OnCollisionPacmanChasingGhost(int pacmanEntityId, int blueGhostEntityId)
	{
		// That's gonna make the ghost stop moving, and make pacman uncontrollable, until PACMAN starts its animation
		Engine::Messager::Fire(
			make_shared<Engine::LogicEvent>(
				Engine::Event::Key(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::GhostTouchesPacman),
					pacmanEntityId
				),
				nullptr));

		// Delay pacman death animation by a constant
		Engine::Messager::Fire(
			make_shared<Engine::EntityEvent>(
				Engine::Event::Key(
					static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), 
				Engine::EntityEvent::Type::Create, 
				L"DelayPacmanDeathEvent", 
				EntityIdCounter::GenerateEntityId(), 
				make_shared<DelayedEventCreatedPayload>(
					Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::PacmanStartDyingAnimation)),
					CollisionConstants::frameBetweenGhostTouchesPacmanAndPacmanStartDying)));
	}
	void CollisionLogicComponent::OnCollisionPacmanSmallDot(int pacmanEntityId, int dotEntityId)
	{
		Engine::Messager::Fire(
			make_shared<Engine::EntityEvent>(
				Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), 
				Engine::EntityEvent::Type::Delete, 
				L"SmallDot", 
				dotEntityId, 
				nullptr));
	}

	void CollisionLogicComponent::OnCollisionPacmanBigDot(int pacmanEntityId, int bigDotEntityId)
	{
		Engine::Messager::Fire(
			make_shared<Engine::EntityEvent>(
				Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)),
				Engine::EntityEvent::Type::Delete,
				L"BigDot",
				bigDotEntityId,
				nullptr));

		Engine::Messager::Fire(
			make_shared<Engine::LogicEvent>(
				Engine::Event::Key(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::BigDotEaten)
				),
				nullptr));
	}
}