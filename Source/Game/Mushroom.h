#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
using namespace Engine;
namespace Game
{
	struct MushroomState
	{
		int posX;
		int posY;
	};

	class MoveMushroomLogicEvent : public IGameLogicEvent
	{
	public:
		enum Direction {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		MoveMushroomLogicEvent(int deltaX, int deltaY);
		~MoveMushroomLogicEvent() = default;

		int GetDeltaX() const { return deltaX; };
		int GetDeltaY() const { return deltaY; };
	private:
		int deltaX;
		int deltaY;
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
		shared_ptr<LogicEvent> CreateMoveEvent(MoveMushroomLogicEvent::Direction direction);
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
		int m_EntityId;
		shared_ptr<MushroomState> m_State;
	};
}