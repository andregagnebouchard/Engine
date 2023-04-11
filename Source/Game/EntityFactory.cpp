#include "stdafx.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Mushroom.h"
namespace Game
{
	shared_ptr<Engine::IEntity> EntityFactory::Create(const wstring &name)
	{
		shared_ptr<MushroomState> state = make_shared<MushroomState>();
		if (name == L"Mushroom")
		{
			vector<shared_ptr<IComponent>> components;
			components.emplace_back(make_shared<MushroomLogicComponent>(1, state));
			components.emplace_back(make_shared<MushroomGraphicComponent>(1, state));
			components.emplace_back(make_shared<MushroomInputComponent>(1));
			return make_shared<Entity>(name, components);
		}
		return nullptr;
	}
}