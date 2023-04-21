#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
using namespace Engine;
namespace Game
{
	struct PauseState
	{
		bool isPaused;
	};

	class PauseGraphicComponent : public IComponent
	{
	public:
		PauseGraphicComponent(int entityId, const shared_ptr<PauseState> state);
		~PauseGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PauseGraphicComponent"; }
		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		int m_EntityId;
		const shared_ptr<PauseState> m_State;
	};

	class PauseInputComponent : public IComponent
	{
	public:
		PauseInputComponent(int entityId);
		~PauseInputComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PauseInputComponent"; }
		Type GetType() const override { return IComponent::Type::Input; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		int m_EntityId;
	};

	class PauseLogicComponent : public IComponent
	{
	public:
		PauseLogicComponent(int entityId, shared_ptr<PauseState> state);
		~PauseLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PauseLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		shared_ptr<PauseState> m_PauseState;
		MessageQueue m_MsgQueue;
		int m_EntityId;
	};
}