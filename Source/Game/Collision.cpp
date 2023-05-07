#include "stdafx.h"
#include <Engine\EventDefinition.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include "Collision.h"
#include "CollisionEvent.h"
#include "GameEventIds.h"
#include "StateContainer.h"
#include <functional>
using namespace Engine;
namespace Game
{
	CollisionLogicComponent::CollisionLogicComponent(int entityId, StateContainer* stateContainer, const unordered_map<int, Entity::Type>* entityIdToType) :
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

	void CollisionLogicComponent::OnCollision(shared_ptr<Event> event)
	{
		if (event->GetType() != Event::Type::Logic)
			throw invalid_argument("CollisionLogicComponent received a non logic event");

		auto ev = dynamic_pointer_cast<LogicEvent>(event);
		auto collisionEvent = dynamic_pointer_cast<CollisionEvent>(ev->GetGameLogicEvent());
		Entity::Type type1 = m_EntityIdToType->at(collisionEvent->GetEntityId1());
		Entity::Type type2 = m_EntityIdToType->at(collisionEvent->GetEntityId2());
		int id1 = collisionEvent->GetEntityId2();
		int id2 = collisionEvent->GetEntityId2();
		if (type1 == Entity::Type::SmallDot && type2 == Entity::Type::Pacman)
			OnCollisionPacmanSmallDot(id2, id1);
		else if (type1 == Entity::Type::Pacman && type2 == Entity::Type::SmallDot)
			OnCollisionPacmanSmallDot(id1, id2);
		else if (type1 == Entity::Type::Pacman && type2 == Entity::Type::BigDot)
			OnCollisionPacmanBigDot(id1, id2);
		else if (type1 == Entity::Type::BigDot && type2 == Entity::Type::Pacman)
			OnCollisionPacmanSmallDot(id2, id1);
		else if (type1 == Entity::Type::BlueGhost && type2 == Entity::Type::Pacman)
			OnColisionPacmanBlueGhost(id2, id1);
		else if (type1 == Entity::Type::Pacman && type2 == Entity::Type::BlueGhost)
			OnColisionPacmanBlueGhost(id1, id2);
	}

	void CollisionLogicComponent::OnColisionPacmanBlueGhost(int pacmanEntityId, int blueGhostEntityId)
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
		Engine::Messager::Fire(
			make_shared<Engine::LogicEvent>(
				Engine::Event::Key(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::GhostKillPacman),
					pacmanEntityId
				),
				nullptr));
	}
	void CollisionLogicComponent::OnCollisionPacmanSmallDot(int pacmanEntityId, int dotEntityId)
	{
		Engine::Messager::Fire(
			make_shared<Engine::EntityEvent>(
				Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), 
				Engine::EntityEvent::Type::Delete, 
				L"SmallDot", 
				dotEntityId, 
				Engine::Point{ -1, -1 }));
	}

	void CollisionLogicComponent::OnCollisionPacmanBigDot(int pacmanEntityId, int bigDotEntityId)
	{
		Engine::Messager::Fire(
			make_shared<Engine::EntityEvent>(
				Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)),
				Engine::EntityEvent::Type::Delete,
				L"BigDot",
				bigDotEntityId,
				Engine::Point{ -1, -1 }));

		Engine::Messager::Fire(
			make_shared<Engine::LogicEvent>(
				Engine::Event::Key(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::BigDotEaten)
				),
				nullptr));
	}
}