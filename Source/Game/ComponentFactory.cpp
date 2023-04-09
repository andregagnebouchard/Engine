#include "stdafx.h"
#include "ComponentFactory.h"
#include "Mushroom.h"

namespace Game
{
	static shared_ptr<MushroomState> state = make_shared<MushroomState>();
	shared_ptr<IComponent> ComponentFactory::Create(const wstring &name)
	{
		if(name == L"MushroomLogicComponent")
		{
			return make_shared<MushroomLogicComponent>(1, state);
		}
		else if (name == L"MushroomGraphicComponent")
		{
			return make_shared<MushroomGraphicComponent>(1, state);
		}
		else if (name == L"MushroomInputComponent")
		{
			return make_shared<MushroomInputComponent>(1);
		}
		return nullptr;
	}
}