#pragma once
#include <Engine\IEntityFactory.h>
#include <Engine\IEntity.h>
#include "Entity.h"
#include "PacmanState.h"
#include "PauseState.h"
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;
namespace Game
{
	class EntityFactory : public Engine::IEntityFactory
	{
	public:
		~EntityFactory() = default;
		shared_ptr<Engine::IEntity> Create(const wstring& name, int entityId) override;
		void Delete(int entityId) override;
	private:
		PacmanState m_PacmanState;
		PauseState m_PauseState;
		unordered_map<int, Entity::Type> m_EntityIdToEntityType;
	};
}
