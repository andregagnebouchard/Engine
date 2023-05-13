#pragma once
#include <Engine\IEntityFactory.h>
#include <Engine\Entity.h>
#include <Engine\WorldGrid.h>
#include "EntityTypes.h"
#include "StateContainer.h"
#include "GhostMovementBehaviour.h"
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;
namespace Game
{
	class EntityFactory : public Engine::IGameEntityFactory
	{
	public:
		EntityFactory();
		~EntityFactory() = default;

		// IEntityFactory
		shared_ptr<Engine::Entity> Create(shared_ptr<EntityEvent> event) override;
		void Delete(int entityId) override;

	private:
		StateContainer m_StateContainer;
		Engine::WorldGrid m_WorldGrid;
		unordered_map<int, EntityType> m_EntityIdToEntityType;
		BlueGhostMovementBehaviour m_BlueGhostBehaviour; // TEmporary to test
	};
}
