#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\Grid.h>
#include "GhostState.h"
#include "GhostMovementBehaviour.h"
#include "EntityTypes.h"
namespace Game
{
	class MoveEvent;

	enum GhostType
	{
		Blue,
		Pink,
		Orange,
		Red
	};

	namespace GhostConstants
	{
		const int chasingFramePerWobbling = 5;
		const int fleeingFramePerWobling = 5;
		const int fleeingFrameBeforeFirstFlash = 150; // Amount of time spent flying before starting to flash
		const int fleeingFlashFrameDuration = 15; // Time spent in each white and blue flash sprite while flashing
		const int fleeingFlashCountBeforeChasing = 10;
		const int fleeingEnd = fleeingFrameBeforeFirstFlash + fleeingFlashCountBeforeChasing * fleeingFlashFrameDuration;
		const float moveDistanceByFrame = 0.0f; // Don't move, just for testing
	};

	class GhostLogicComponent : public Engine::IComponent
	{
	public:
		GhostLogicComponent(int entityId, GhostState *state, const Engine::Grid *worldGrid, const unordered_map<int, EntityType>* entityIdToEntityType, const IGhostMovementBehaviour *movementBehaviour);
		~GhostLogicComponent() = default;
		void Init() override;
		void Shutdown() override;
		void OnEvent(const shared_ptr<Engine::Event> event);
		void Update() override;

		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:

		void ChasingLogicUpdate();
		void FleeingLogicUpdate();
		void RespawningLogicUpdate();
		void WaitingForPacmanDyingLogicUpdate();
		void KillYourself();
		const unordered_map<int, EntityType> *m_EntityIdToEntityType; // Owner is EntityFactory
		const Engine::Grid* m_WorldGrid; // Owner is EntityFactory
		const function<void(shared_ptr<Engine::Event>)> m_EventCallback;
		const int m_EntityId;
		GhostState *m_State; // Owner is EntityFactory
		const IGhostMovementBehaviour* m_MovementBehaviour; // Owner is EntityFactory
	};

	class GhostGraphicComponent : public Engine::IComponent
	{
	public:
		GhostGraphicComponent(int entityId, const GhostState *state, GhostType type);
		~GhostGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		void ChasingUpdate() const;
		void FleeingUpdate() const;
		void RespawningUpdate() const;

		const int m_EntityId;
		const GhostState* m_State; // Owner is EntityFactory
		const GhostType m_Type;
	};
}