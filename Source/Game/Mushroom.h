#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
using namespace Engine;
namespace Game
{
	enum MushroomMovingDirection { LEFT, UP, RIGHT, DOWN };
	enum MushroomActionState { IDLE, MOVING };
	struct MushroomState
	{
		float posX;
		float posY;
		MushroomActionState actionState;
		MushroomMovingDirection direction;
		int movingFrame;
	};

	class MoveMushroomLogicEvent : public IGameLogicEvent
	{
	public:
		MoveMushroomLogicEvent(int deltaX, int deltaY, MushroomMovingDirection direction);
		~MoveMushroomLogicEvent() = default;

		int GetDeltaX() const { return m_DeltaX; };
		int GetDeltaY() const { return m_DeltaY; };
		MushroomMovingDirection GetDirection() const { return m_Direction; };
	private:
		int m_DeltaX;
		int m_DeltaY;
		MushroomMovingDirection m_Direction;
	};

	class MushroomInputComponent : public IComponent
	{
	public:
		MushroomInputComponent(int entityId);
		~MushroomInputComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomInputComponent"; }
		Type GetType() const override { return IComponent::Type::Input; }
	private:
		shared_ptr<LogicEvent> CreateMoveEvent(MushroomMovingDirection direction);
		MessageQueue m_MsgQueue;
		int m_EntityId;

	};

	class MushroomLogicComponent : public IComponent
	{
	public:
		MushroomLogicComponent(int entityId, shared_ptr<MushroomState> state);
		~MushroomLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
	private:
		void Move(shared_ptr<MoveMushroomLogicEvent> ev);
		MessageQueue m_MsgQueue;
		int m_EntityId;
		shared_ptr<MushroomState> m_State;
	};

	class MushroomGraphicComponent : public IComponent
	{
	public:
		MushroomGraphicComponent(int entityId, shared_ptr<MushroomState> state);
		~MushroomGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomGraphicComponent"; }
		Type GetType() const override { return IComponent::Type::Graphic; }
	private:
		wstring PickSpriteName() const;
		int m_EntityId;
		shared_ptr<MushroomState> m_State;
	};

	class MushroomAudioComponent : public IComponent
	{
	public:
		MushroomAudioComponent(int entityId);
		~MushroomAudioComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomAudioComponent"; }
		Type GetType() const override { return IComponent::Type::Audio; }
	private:
		shared_ptr<AudioEvent> CreateAudioEvent() const;
		MessageQueue m_MsgQueue;
		int m_EntityId;
	};
}