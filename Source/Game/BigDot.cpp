#include "stdafx.h"
#include "BigDot.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	BigDotGraphicComponent::BigDotGraphicComponent(int entityId, PackedArray<BigDotState, 32>* states) :
		m_EntityId(entityId),
		m_States(states)
	{
	}

	void BigDotGraphicComponent::Update(float dt)
	{
		const BigDotState* state = m_States->GetData(m_EntityId);
		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			L"big_dot",
			state->positionX,
			state->positionY));
	}
}