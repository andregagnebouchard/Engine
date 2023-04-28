#include "stdafx.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Pacman.h"
#include "Pause.h"
namespace Game
{
	shared_ptr<Engine::IEntity> EntityFactory::Create(const wstring &name, int entityId)
	{
		vector<shared_ptr<IComponent>> components;
		if (name == L"Pacman")
		{
			components.emplace_back(make_shared<PacmanLogicComponent>(entityId, &m_PacmanState));
			components.emplace_back(make_shared<PacmanGraphicComponent>(entityId, &m_PacmanState));
			components.emplace_back(make_shared<PacmanInputComponent>(entityId));
			components.emplace_back(make_shared<PacmanAudioComponent>(entityId));

			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Pacman);
			return make_shared<Entity>(name, components);
		}
		else if(name == L"Pause")
		{
			components.emplace_back(make_shared<PauseGraphicComponent>(entityId, &m_PauseState));
			components.emplace_back(make_shared<PauseInputComponent>(entityId));
			components.emplace_back(make_shared<PauseLogicComponent>(entityId, &m_PauseState));
			m_EntityIdToEntityType.emplace(entityId, Entity::Type::Pause);
			return make_shared<Entity>(name, components);
		}
		return nullptr;
	}

	void EntityFactory::Delete(int entityId)
	{
		if (m_EntityIdToEntityType.find(entityId) == m_EntityIdToEntityType.end())
			throw std::runtime_error("The entity id does not exist");
		m_EntityIdToEntityType.erase(entityId);
	}

	Entity::Type EntityFactory::GetEntityType(int entityId) const
	{
		return m_EntityIdToEntityType.at(entityId);
	}
}