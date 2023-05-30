#include "stdafx.h"
#include "BigDot.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	BigDotLogicComponent::BigDotLogicComponent(int entityId, PackedArray<BigDotState, 32>* states) :
		m_EntityId(entityId),
		m_States(states)
	{
	}

	void BigDotLogicComponent::Update()
	{
		Blink();
	}

	void BigDotLogicComponent::Blink()
	{
		BigDotState* state = m_States->GetData(m_EntityId);
		if (state->animationFrame < 2 * BigDotConstants::frameCountBetweenEachBlink) // There are 2 frames in the animation
			state->animationFrame++;
		else
			state->animationFrame = 0;
	}

	BigDotGraphicComponent::BigDotGraphicComponent(int entityId, PackedArray<BigDotState, 32>* states) :
		m_EntityId(entityId),
		m_States(states)
	{
	}

	void BigDotGraphicComponent::Update()
	{
		const BigDotState* state = m_States->GetData(m_EntityId);
		bool isVisible = state->animationFrame < BigDotConstants::frameCountBetweenEachBlink;
		if(isVisible)
			Messager::Fire(make_shared<RenderSpriteEvent>(
				Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
				L"big_dot",
				state->positionX,
				state->positionY));
	}
}