#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
using namespace Engine;
namespace Game
{
	enum PacmanMovingDirection { LEFT, UP, RIGHT, DOWN };
	enum PacmanActionState { IDLE, MOVING };
	struct PacmanState
	{
		float posX;
		float posY;
		PacmanActionState actionState;
		PacmanMovingDirection direction;
		int movingFrame;
	};

	class MovePacmanLogicEvent : public IGameLogicEvent
	{
	public:
		MovePacmanLogicEvent(int deltaX, int deltaY, PacmanMovingDirection direction);
		~MovePacmanLogicEvent() = default;

		int GetDeltaX() const { return m_DeltaX; };
		int GetDeltaY() const { return m_DeltaY; };
		PacmanMovingDirection GetDirection() const { return m_Direction; };
	private:
		int m_DeltaX;
		int m_DeltaY;
		PacmanMovingDirection m_Direction;
	};

	class PacmanInputComponent : public IComponent
	{
	public:
		PacmanInputComponent(int entityId);
		~PacmanInputComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PacmanInputComponent"; }
		Type GetType() const override { return IComponent::Type::Input; }
		int GetId() const override { return m_EntityId; };
	private:
		shared_ptr<LogicEvent> CreateMoveEvent(PacmanMovingDirection direction);
		MessageQueue m_MsgQueue;
		int m_EntityId;

	};

	class PacmanLogicComponent : public IComponent
	{
	public:
		PacmanLogicComponent(int entityId, shared_ptr<PacmanState> state);
		~PacmanLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PacmanLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		void Move(shared_ptr<MovePacmanLogicEvent> ev);
		MessageQueue m_MsgQueue;
		int m_EntityId;
		shared_ptr<PacmanState> m_State;
	};

	class PacmanGraphicComponent : public IComponent
	{
	public:
		PacmanGraphicComponent(int entityId, shared_ptr<PacmanState> state);
		~PacmanGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PacmanGraphicComponent"; }
		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		wstring PickSpriteName() const;
		int m_EntityId;
		shared_ptr<PacmanState> m_State;
	};

	class PacmanAudioComponent : public IComponent
	{
	public:
		PacmanAudioComponent(int entityId);
		~PacmanAudioComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"PacmanAudioComponent"; }
		Type GetType() const override { return IComponent::Type::Audio; }
		int GetId() const override { return m_EntityId; };
	private:
		shared_ptr<AudioEvent> CreateAudioEvent() const;
		MessageQueue m_MsgQueue;
		int m_EntityId;
	};
}