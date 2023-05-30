#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include "PauseState.h"
using namespace Engine;
namespace Game
{
	class PauseGraphicComponent : public IComponent
	{
	public:
		PauseGraphicComponent(int entityId, const PauseState *state);
		~PauseGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		const int m_EntityId;
		const PauseState* m_State;
	};

	class PauseInputComponent : public IComponent
	{
	public:
		PauseInputComponent(int entityId);
		~PauseInputComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Input; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		const int m_EntityId;
	};

	class PauseLogicComponent : public IComponent
	{
	public:
		PauseLogicComponent(int entityId, PauseState* state);
		~PauseLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		PauseState* m_PauseState;
		MessageQueue m_MsgQueue;
		const int m_EntityId;
	};
}