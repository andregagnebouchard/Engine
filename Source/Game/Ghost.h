#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\WorldGrid.h>
#include "GhostState.h"
#include "GhostMovementBehaviour.h"
#include "Entity.h"
using namespace Engine;
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
		const int chasingFramePerSprite = 5;
		const int fleeingFramePerWobling = 5;
		const int fleeingFrameBeforeFirstFlash = 150;
		const int fleeingFlashFrameDuration = 15;
		const int fleeingFlashCountBeforeChasing = 10;
		const int fleeingEnd = fleeingFrameBeforeFirstFlash + fleeingFlashCountBeforeChasing * fleeingFlashFrameDuration;
		const float moveDistanceByFrame = 0.0f; // Don't move, just for testing
	};

	class GhostLogicComponent : public IComponent
	{
	public:
		GhostLogicComponent(int entityId, GhostState *state, const WorldGrid *worldGrid, const unordered_map<int, Entity::Type>* entityIdToEntityType, const IGhostMovementBehaviour *movementBehaviour);
		~GhostLogicComponent() = default;
		void Init() override;
		void Shutdown() override;
		void Update() override;

		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:

		void ProcessEvents();
		void TickLogic();
		void ChasingLogicUpdate();
		void FleeingLogicUpdate();
		void RespawningLogicUpdate();
		void WaitingForPacmanDyingLogicUpdate();
		void KillYourself();
		const unordered_map<int, Entity::Type> *m_EntityIdToEntityType; // Owner is EntityFactory
		const WorldGrid* m_WorldGrid; // Owner is EntityFactory
		MessageQueue m_MsgQueue;
		int m_EntityId;
		GhostState *m_State; // Owner is EntityFactory
		const IGhostMovementBehaviour* m_MovementBehaviour; // Owner is EntityFactory
	};

	class GhostGraphicComponent : public IComponent
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

		int m_EntityId;
		const GhostState* m_State; // Owner is EntityFactory
		const GhostType m_Type;
	};
}