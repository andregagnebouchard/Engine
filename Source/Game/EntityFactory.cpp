#include "stdafx.h"
#include <Engine/DelayedEventLogicComponent.h>
#include <Engine/EventDefinition.h>
#include "EntityCreatedPayload.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Pacman.h"
#include "Pause.h"
#include "SmallDot.h"
#include "BigDot.h"
#include "Collision.h"
#include "Debug.h"
#include "Ghost.h"
#include "LevelGenerator.h"
#include "Grid.h"
#include "GameEventIds.h"
namespace Game
{
	EntityFactory::EntityFactory() :
		m_WorldGrid(32, 32),
		m_BlueGhostBehaviour(&m_WorldGrid, &m_EntityIdToEntityType)
	{

	}
	shared_ptr<Engine::IEntity> EntityFactory::Create(shared_ptr<EntityEvent> event)
	{
		const wstring& name = event->GetName();
		const int entityId = event->GetEntityId();

		vector<shared_ptr<IComponent>> components;
		if (name == L"Pacman")
		{
			components.emplace_back(make_shared<PacmanLogicComponent>(entityId, &m_StateContainer.pacmanState, &m_WorldGrid, &m_EntityIdToEntityType));
			components.emplace_back(make_shared<PacmanGraphicComponent>(entityId, &m_StateContainer.pacmanState));
			components.emplace_back(make_shared<PacmanInputComponent>(entityId));
			components.emplace_back(make_shared<PacmanAudioComponent>(entityId));

			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Pacman);
			return make_shared<Entity>(name, components);
		}
		else if(name == L"Pause")
		{
			components.emplace_back(make_shared<PauseGraphicComponent>(entityId, &m_StateContainer.pauseState));
			components.emplace_back(make_shared<PauseInputComponent>(entityId));
			components.emplace_back(make_shared<PauseLogicComponent>(entityId, &m_StateContainer.pauseState));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Pause);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"Collision")
		{
			components.emplace_back(make_shared<CollisionLogicComponent>(entityId, &m_StateContainer, &m_EntityIdToEntityType));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Collision);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"SmallDot")
		{
			// Not sure whether entity factory should init the state, but it's certainly better than the graphic component
			SmallDotState state;
			const Point &position= dynamic_pointer_cast<PositionPayload>(event->GetPayload())->GetPosition();
			state.positionX = position.x;
			state.positionY = position.y;
			m_StateContainer.smallDotStates.Add(state, entityId);

			components.emplace_back(make_shared<SmallDotGraphicComponent>(entityId, &m_StateContainer.smallDotStates));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::SmallDot);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"BigDot")
		{
			// Not sure whether entity factory should init the state, but it's certainly better than the graphic component
			BigDotState state;
			const Point& position = dynamic_pointer_cast<PositionPayload>(event->GetPayload())->GetPosition();
			state.positionX = position.x;
			state.positionY = position.y;
			m_StateContainer.bigDotStates.Add(state, entityId);

			components.emplace_back(make_shared<BigDotGraphicComponent>(entityId, &m_StateContainer.bigDotStates));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::BigDot);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"Grid")
		{
			components.emplace_back(make_shared<GridLogicComponent>(entityId, &m_WorldGrid));
			components.emplace_back(make_shared<GridGraphicComponent>(entityId, &m_WorldGrid, &m_StateContainer.debugState));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Grid);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"LevelGenerator")
		{
			components.emplace_back(make_shared<LevelGeneratorLogicComponent>(entityId));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::LevelGenerator);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"Debug")
		{
			components.emplace_back(make_shared<DebugLogicComponent>(entityId, &m_StateContainer.debugState));
			components.emplace_back(make_shared<DebugInputComponent>(entityId));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Debug);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"BlueGhost")
		{
			// Not sure whether entity factory should init the state, but it's certainly better than the graphic component
			const Point& position = dynamic_pointer_cast<PositionPayload>(event->GetPayload())->GetPosition();
			m_StateContainer.blueGhostState.positionX = position.x;
			m_StateContainer.blueGhostState.positionY = position.y;
			components.emplace_back(make_shared<GhostGraphicComponent>(entityId, &m_StateContainer.blueGhostState, GhostType::Blue));
			components.emplace_back(make_shared<GhostLogicComponent>(entityId, &m_StateContainer.blueGhostState, &m_WorldGrid, &m_EntityIdToEntityType, &m_BlueGhostBehaviour));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::BlueGhost);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"DelayPacmanDeathEvent")
		{
			auto payload = dynamic_pointer_cast<DelayedEventCreatedPayload>(event->GetPayload());
			components.emplace_back(make_shared<DelayedEventLogicComponent>(entityId, payload->GetDelayTickCount(), payload->GetKeyToEmit()));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::DelayPacmanDeathEvent);
			return make_shared<Entity>(name, components);
		}
		return nullptr;
	}

	void EntityFactory::Delete(int entityId)
	{
		if (m_EntityIdToEntityType.at(entityId) == Entity::Type::SmallDot)
			m_StateContainer.smallDotStates.Delete(entityId);
		m_EntityIdToEntityType.erase(entityId);
	}
}