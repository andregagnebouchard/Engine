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
			shared_ptr<PacmanState> state = make_shared<PacmanState>();
			components.emplace_back(make_shared<PacmanLogicComponent>(entityId, state));
			components.emplace_back(make_shared<PacmanGraphicComponent>(entityId, state));
			components.emplace_back(make_shared<PacmanInputComponent>(entityId));
			components.emplace_back(make_shared<PacmanAudioComponent>(entityId));
			return make_shared<Entity>(name, components);
		}
		else if(name == L"Pause")
		{
			vector<shared_ptr<IComponent>> components;
			components.emplace_back(make_shared<PauseInputComponent>(entityId));
			components.emplace_back(make_shared<PauseLogicComponent>(entityId));
			return make_shared<Entity>(name, components);
		}
		return nullptr;
	}
}