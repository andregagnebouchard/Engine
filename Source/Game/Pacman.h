#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\Grid.h>
#include "PacmanState.h"
#include "EntityTypes.h"
namespace Game
{
	namespace PacmanConstants
	{
		const int dyingAnimationSpriteCount = 11;
		const float moveDistanceByFrame = 32;
		const int framePerDyingAnimationSprite = 6;
		const int dyingAnimationLength = dyingAnimationSpriteCount * framePerDyingAnimationSprite;
	}
	class MoveEvent;
	class PacmanInputMoveEvent : public Engine::IGameLogicEvent
	{
	public:
		enum Direction
		{
			Up,
			Down,
			Left,
			Right
		};
		PacmanInputMoveEvent(Direction direction);
		~PacmanInputMoveEvent() = default;

		Direction GetDirection() const { return m_Direction; };
	private:
		Direction m_Direction;
	};

	class PacmanInputComponent : public Engine::IComponent
	{
	public:
		PacmanInputComponent(int entityId);
		~PacmanInputComponent() = default;
		void Init() override;
		void Shutdown() override;
		void Update() override;

		Type GetType() const override { return IComponent::Type::Input; }
		int GetId() const override { return m_EntityId; };
	private:
		shared_ptr<Engine::LogicEvent> CreateMoveEvent(PacmanState::MovingDirection direction);
		Engine::MessageQueue m_MsgQueue;
		int m_EntityId;
	};

	class PacmanLogicComponent : public Engine::IComponent
	{
	public:
		PacmanLogicComponent(int entityId, PacmanState *state, Engine::Grid *worldGrid, const unordered_map<int, EntityType>* entityIdToEntityType);
		~PacmanLogicComponent() = default;
		void Init() override;
		void Shutdown() override;
		void Update() override;

		Type GetType() const override { return Engine::IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		void ProcessEvents();
		void TryMove(shared_ptr<PacmanInputMoveEvent> ev);
		void UpdateDyingLogic();
		void StopMoving();

		const unordered_map<int, EntityType> *m_EntityIdToEntityType; // Owner is EntityFactory
		Engine::Grid* m_WorldGrid; // Owner is EntityFactory
		Engine::MessageQueue m_MsgQueue;
		int m_EntityId;
		PacmanState *m_State; // Owner is EntityFactory
	};

	class PacmanGraphicComponent : public Engine::IComponent
	{
	public:
		PacmanGraphicComponent(int entityId, const PacmanState *state);
		~PacmanGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return Engine::IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		wstring PickSpriteName() const;
		wstring PickMovingSprite() const;
		wstring PickDyingSprite() const;
		int m_EntityId;
		const PacmanState* m_State; // Owner is EntityFactory
	};

	class PacmanAudioComponent : public Engine::IComponent
	{
	public:
		PacmanAudioComponent(int entityId);
		~PacmanAudioComponent() = default;
		void Init() override;
		void Shutdown() override;
		void Update() override;

		Type GetType() const override { return Engine::IComponent::Type::Audio; }
		int GetId() const override { return m_EntityId; };
	private:
		shared_ptr<Engine::AudioEvent> CreateAudioEvent() const;
		Engine::MessageQueue m_MsgQueue;
		int m_EntityId;
	};
}