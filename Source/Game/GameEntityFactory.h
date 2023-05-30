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
	// This class is called by the engine to create and delete game specific entities, defined in the game outside of the engine
	class GameEntityFactory : public Engine::IGameEntityFactory
	{
	public:
		GameEntityFactory();
		~GameEntityFactory() = default;

		// IGameEntityFactory
		shared_ptr<Engine::Entity> Create(shared_ptr<EntityEvent> event) override;
		void Delete(int entityId) override;

	private:

		shared_ptr<Engine::Entity> CreatePacman(int entityId, const wstring& name);
		shared_ptr<Engine::Entity> CreatePause(int entityId, const wstring& name);
		shared_ptr<Engine::Entity> CreateCollision(int entityId, const wstring& name);
		shared_ptr<Engine::Entity> CreateSmallDot(int entityId, const wstring& name, const shared_ptr<EntityEvent> event);
		shared_ptr<Engine::Entity> CreateBigDot(int entityId, const wstring& name, const shared_ptr<EntityEvent> event);
		shared_ptr<Engine::Entity> CreateGrid(int entityId, const wstring& name);
		shared_ptr<Engine::Entity> CreateLevelGenerator(int entityId, const wstring& name);
		shared_ptr<Engine::Entity> CreateDebug(int entityId, const wstring& name);
		shared_ptr<Engine::Entity> CreateBlueGhost(int entityId, const wstring& name, const shared_ptr<EntityEvent> event);
		shared_ptr<Engine::Entity> CreateDelayPacmanDeathEvent(int entityId, const wstring& name, const shared_ptr<EntityEvent> event);
		StateContainer m_StateContainer;
		Engine::Grid m_Grid;
		unordered_map<int, EntityType> m_EntityIdToEntityType;
		BlueGhostMovementBehaviour m_BlueGhostBehaviour; // TEmporary to test
	};
}
