#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\PackedArray.h>
#include "BigDotState.h"
using namespace Engine;
namespace Game
{
	namespace BigDotConstants
	{
		const int frameBetweenEachBlink = 10;
	}

	class BigDotLogicComponent : public IComponent
	{
	public:
		BigDotLogicComponent(int entityId, PackedArray<BigDotState, 32>* states);
		~BigDotLogicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		wstring GetName() const override { return L"BigDotLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		PackedArray<BigDotState, 32>* m_States; // EntityFactory is the owner
		int m_EntityId;
	};

	class BigDotGraphicComponent : public IComponent
	{
	public:
		BigDotGraphicComponent(int entityId, PackedArray<BigDotState, 32>* states);
		~BigDotGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		wstring GetName() const override { return L"BigDotGraphicComponent"; }
		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		PackedArray<BigDotState, 32>* m_States; // EntityFactory is the owner
		int m_EntityId;
	};
}