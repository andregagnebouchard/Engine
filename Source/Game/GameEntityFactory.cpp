#include "stdafx.h"
#include <Engine/DelayedEventLogicComponent.h>
#include <Engine/EventDefinition.h>
#include "EntityCreatedPayload.h"
#include "GameEntityFactory.h"
#include "EntityTypes.h"
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
	GameEntityFactory::GameEntityFactory() :
		m_Grid(32, 32),
		m_BlueGhostBehaviour(&m_Grid, &m_EntityIdToEntityType)
	{
	}
	shared_ptr<Engine::Entity> GameEntityFactory::Create(shared_ptr<EntityEvent> event)
	{
		const wstring& name = event->GetName();
		const int entityId = event->GetEntityId();

		if (name == L"Pacman")
			return CreatePacman(entityId, name);
		else if (name == L"Pause")
			return CreatePause(entityId, name);
		else if (name == L"Collision")
			return CreateCollision(entityId, name);
		else if (name == L"SmallDot")
			return CreateSmallDot(entityId, name, event);
		else if (name == L"BigDot")
			return CreateBigDot(entityId, name, event);
		else if (name == L"Grid")
			return CreateGrid(entityId, name);
		else if (name == L"LevelGenerator")
			return CreateLevelGenerator(entityId, name);
		else if (name == L"Debug")
			return CreateDebug(entityId, name);
		else if (name == L"BlueGhost")
			return CreateBlueGhost(entityId, name, event);
		else if (name == L"DelayPacmanDeathEvent")
			return CreateDelayPacmanDeathEvent(entityId, name, event);
		return nullptr;
	}

	void GameEntityFactory::Delete(int entityId)
	{
		if (m_EntityIdToEntityType.at(entityId) == EntityType::SmallDot)
			m_StateContainer.smallDotStates.Delete(entityId);
		m_EntityIdToEntityType.erase(entityId);
	}

	shared_ptr<Engine::Entity> GameEntityFactory::CreatePacman(int entityId, const wstring& name)
	{
		vector<shared_ptr<IComponent>> components;
		components.emplace_back(make_shared<PacmanLogicComponent>(entityId, &m_StateContainer.pacmanState, &m_Grid, &m_EntityIdToEntityType));
		components.emplace_back(make_shared<PacmanGraphicComponent>(entityId, &m_StateContainer.pacmanState));
		components.emplace_back(make_shared<PacmanInputComponent>(entityId));
		components.emplace_back(make_shared<PacmanAudioComponent>(entityId));

		m_EntityIdToEntityType.emplace(entityId, EntityType::Pacman);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreatePause(int entityId, const wstring& name)
	{
		vector<shared_ptr<IComponent>> components;
		components.emplace_back(make_shared<PauseGraphicComponent>(entityId, &m_StateContainer.pauseState));
		components.emplace_back(make_shared<PauseInputComponent>(entityId));
		components.emplace_back(make_shared<PauseLogicComponent>(entityId, &m_StateContainer.pauseState));
		m_EntityIdToEntityType.emplace(entityId, EntityType::Pause);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateCollision(int entityId, const wstring& name)
	{
		vector<shared_ptr<IComponent>> components;
		components.emplace_back(make_shared<CollisionLogicComponent>(entityId, &m_StateContainer, &m_EntityIdToEntityType));
		m_EntityIdToEntityType.emplace(entityId, EntityType::Collision);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateSmallDot(int entityId, const wstring& name, const shared_ptr<EntityEvent> event)
	{
		vector<shared_ptr<IComponent>> components;

		// Not sure whether entity factory should init the state, but it's certainly better than the graphic component
		SmallDotState state;
		const Point& position = dynamic_pointer_cast<PositionPayload>(event->GetPayload())->GetPosition();
		state.positionX = position.x;
		state.positionY = position.y;
		m_StateContainer.smallDotStates.Add(state, entityId);

		components.emplace_back(make_shared<SmallDotGraphicComponent>(entityId, &m_StateContainer.smallDotStates));
		m_EntityIdToEntityType.emplace(entityId, EntityType::SmallDot);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateBigDot(int entityId, const wstring& name, const shared_ptr<EntityEvent> event)
	{
		vector<shared_ptr<IComponent>> components;
		// Not sure whether entity factory should init the state, but it's certainly better than the graphic component
		BigDotState state;
		const Point& position = dynamic_pointer_cast<PositionPayload>(event->GetPayload())->GetPosition();
		state.positionX = position.x;
		state.positionY = position.y;
		m_StateContainer.bigDotStates.Add(state, entityId);

		components.emplace_back(make_shared<BigDotGraphicComponent>(entityId, &m_StateContainer.bigDotStates));
		components.emplace_back(make_shared<BigDotLogicComponent>(entityId, &m_StateContainer.bigDotStates));
		m_EntityIdToEntityType.emplace(entityId, EntityType::BigDot);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateGrid(int entityId, const wstring& name)
	{
		vector<shared_ptr<IComponent>> components;
		components.emplace_back(make_shared<GridLogicComponent>(entityId, &m_Grid));
		components.emplace_back(make_shared<GridGraphicComponent>(entityId, &m_Grid, &m_StateContainer.debugState));
		m_EntityIdToEntityType.emplace(entityId, EntityType::Grid);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateLevelGenerator(int entityId, const wstring& name)
	{
		vector<shared_ptr<IComponent>> components;
		components.emplace_back(make_shared<LevelGeneratorLogicComponent>(entityId));
		m_EntityIdToEntityType.emplace(entityId, EntityType::LevelGenerator);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateDebug(int entityId, const wstring& name)
	{
		vector<shared_ptr<IComponent>> components;
		components.emplace_back(make_shared<DebugLogicComponent>(entityId, &m_StateContainer.debugState));
		components.emplace_back(make_shared<DebugInputComponent>(entityId));
		m_EntityIdToEntityType.emplace(entityId, EntityType::Debug);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateBlueGhost(int entityId, const wstring& name, const shared_ptr<EntityEvent> event)
	{
		vector<shared_ptr<IComponent>> components;

		// Not sure whether entity factory should init the state, but it's certainly better than the graphic component
		const Point& position = dynamic_pointer_cast<PositionPayload>(event->GetPayload())->GetPosition();
		m_StateContainer.blueGhostState.positionX = position.x;
		m_StateContainer.blueGhostState.positionY = position.y;
		components.emplace_back(make_shared<GhostGraphicComponent>(entityId, &m_StateContainer.blueGhostState, GhostType::Blue));
		components.emplace_back(make_shared<GhostLogicComponent>(entityId, &m_StateContainer.blueGhostState, &m_Grid, &m_EntityIdToEntityType, &m_BlueGhostBehaviour));
		m_EntityIdToEntityType.emplace(entityId, EntityType::BlueGhost);
		return make_shared<Entity>(name, components);
	}
	shared_ptr<Engine::Entity> GameEntityFactory::CreateDelayPacmanDeathEvent(int entityId, const wstring& name, const shared_ptr<EntityEvent> event)
	{
		vector<shared_ptr<IComponent>> components;
		auto payload = dynamic_pointer_cast<DelayedEventCreatedPayload>(event->GetPayload());
		components.emplace_back(make_shared<DelayedEventLogicComponent>(entityId, payload->GetDelayTickCount(), payload->GetKeyToEmit()));
		m_EntityIdToEntityType.emplace(entityId, EntityType::DelayPacmanDeathEvent);
		return make_shared<Entity>(name, components);
	}
}