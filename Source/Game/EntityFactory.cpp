#include "stdafx.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Pacman.h"
#include "Pause.h"
#include "SmallDot.h"
#include "Collision.h"
#include "LevelGenerator.h"
#include "Grid.h"
namespace Game
{
	EntityFactory::EntityFactory() :
		m_WorldGrid(32, 32)
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
			state.positionX = event->GetPosition().x;
			state.positionY = event->GetPosition().y;
			m_StateContainer.dotStates.Add(state, entityId);

			components.emplace_back(make_shared<SmallDotGraphicComponent>(entityId, &m_StateContainer.dotStates));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::SmallDot);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"Grid")
		{
			components.emplace_back(make_shared<GridLogicComponent>(entityId, &m_WorldGrid));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Grid);
			return make_shared<Entity>(name, components);
		}
		else if (name == L"LevelGenerator")
		{
			components.emplace_back(make_shared<LevelGeneratorLogicComponent>(entityId));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::LevelGenerator);
			return make_shared<Entity>(name, components);
		}
		return nullptr;
	}

	void EntityFactory::Delete(int entityId)
	{
		if (m_EntityIdToEntityType.at(entityId) == Entity::Type::SmallDot)
			m_StateContainer.dotStates.Delete(entityId);
		m_EntityIdToEntityType.erase(entityId);
	}
}