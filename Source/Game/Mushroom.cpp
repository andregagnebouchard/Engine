#include "stdafx.h"
#include "Mushroom.h"
#include <Engine\Messager.h>
using namespace Engine;
namespace Game
{
	void MushroomGraphicComponent::Update(float dt)
	{
		Messager::Fire(make_shared<RenderEvent>(Event::Id::RENDER_SPRITE, L"Mushroom"));
	}

	MushroomInputComponent::MushroomInputComponent()
	{

	}
	void MushroomInputComponent::Update(float dt)
	{

	}

	void MushroomLogicComponent::Update(float dt)
	{

	}
}