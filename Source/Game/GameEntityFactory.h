#pragma once
#include <Engine\IGameEntityFactory.h>
#include <Engine\Entity.h>
#include <Engine\Grid.h>
#include "EntityTypes.h"
#include "StateContainer.h"
#include "GhostMovementBehaviour.h"
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;
namespace Game
{
	class GameEntityFactory : public Engine::IGameEntityFactory
	{
	public:
		GameEntityFactory();
		~GameEntityFactory() = default;

		// IGameEntityFactory
		shared_ptr<Engine::Entity> Create(shared_ptr<EntityEvent> event) override;
		void Delete(int entityId) override;

	private:
		StateContainer m_StateContainer;
		Engine::Grid m_Grid;
		unordered_map<int, EntityType> m_EntityIdToEntityType;
		BlueGhostMovementBehaviour m_BlueGhostBehaviour; // TEmporary to test
	};
}
