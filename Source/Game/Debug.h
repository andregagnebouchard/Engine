#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
using namespace Engine;
namespace Game
{
	struct DebugState;
	class DebugInputComponent : public IComponent
	{
	public:
		DebugInputComponent(int entityId);
		~DebugInputComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Input; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		int m_EntityId;
	};

	class DebugLogicComponent : public IComponent
	{
	public:
		DebugLogicComponent(int entityId, DebugState *state);
		~DebugLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		DebugState* m_State;
		int m_EntityId;
	};
}