#include "stdafx.h"
#include "ComponentFactory.h"
#include "Mushroom.h"

namespace Game
{
	shared_ptr<IComponent> ComponentFactory::Create(const wstring &name)
	{
		if(name == L"MushroomLogicComponent")
		{
			return make_shared<MushroomLogicComponent>();
		}
		else if (name == L"MushroomGraphicComponent")
		{
			return make_shared<MushroomGraphicComponent>();

		}
		else if (name == L"MushroomInputComponent")
		{
			return make_shared<MushroomInputComponent>();

		}
		return nullptr;
	}
}