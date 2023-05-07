#pragma once
#include <Engine\IEntityFactory.h>
#include <Engine\IEntity.h>
#include <Engine\WorldGrid.h>
#include "Entity.h"
#include "StateContainer.h"
#include "GhostMovementBehaviour.h"
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;
namespace Game
{
	class EntityFactory : public Engine::IEntityFactory
	{
	public:
		EntityFactory();
		~EntityFactory() = default;

		// IEntityFactory
		shared_ptr<Engine::IEntity> Create(shared_ptr<EntityEvent> event) override;
		void Delete(int entityId) override;

	private:
		StateContainer m_StateContainer;
		Engine::WorldGrid m_WorldGrid;
		unordered_map<int, Entity::Type> m_EntityIdToEntityType;
		BlueGhostMovementBehaviour m_BlueGhostBehaviour; // TEmporary to test
	};
}
