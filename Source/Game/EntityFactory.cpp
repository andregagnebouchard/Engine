#include "stdafx.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Mushroom.h"
namespace Game
{
	shared_ptr<Engine::IEntity> EntityFactory::Create(const wstring &name, int entityId)
	{
		shared_ptr<MushroomState> state = make_shared<MushroomState>();
		if (name == L"Mushroom")
		{
			vector<shared_ptr<IComponent>> components;
			components.emplace_back(make_shared<MushroomLogicComponent>(entityId, state));
			components.emplace_back(make_shared<MushroomGraphicComponent>(entityId, state));
			components.emplace_back(make_shared<MushroomInputComponent>(entityId));
			return make_shared<Entity>(name, components);
		}
		return nullptr;
	}
}