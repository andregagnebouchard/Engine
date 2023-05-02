#include "stdafx.h"
#include "SmallDot.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	SmallDotGraphicComponent::SmallDotGraphicComponent(int entityId, PackedArray<SmallDotState, 1024> *states) :
		m_EntityId(entityId),
		m_States(states)
	{
	}

	void SmallDotGraphicComponent::Update(float dt)
	{
		const SmallDotState* state = m_States->GetData(m_EntityId);
		Messager::Fire(make_shared<RenderSpriteEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			L"small_dot",
			state->positionX,
			state->positionY));
	}
}