#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\PackedArray.h>
#include "SmallDotState.h"
using namespace Engine;
namespace Game
{
	class SmallDotGraphicComponent : public IComponent
	{
	public:
		SmallDotGraphicComponent(int entityId, PackedArray<SmallDotState, 1024> *states);
		~SmallDotGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		PackedArray<SmallDotState, 1024> *m_States; // EntityFactory is the owner
		const int m_EntityId;
	};
}