#pragma once
#include <Engine\IComponent.h>
#include "EntityTypes.h"
using namespace Engine;
namespace Game
{
	namespace CollisionConstants
	{
		const int frameBetweenGhostTouchesPacmanAndPacmanStartDying = 40;
	}

	struct StateContainer;
	class CollisionLogicComponent : public IComponent
	{
	public:
		CollisionLogicComponent(int entityId, StateContainer *stateContainer, const unordered_map<int, EntityType> *entityIdToType);
		~CollisionLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update() override {}; // Events are handled synchronously for this one, no need for update

		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		void OnCollision(const shared_ptr<Event> event);
		void OnCollisionPacmanSmallDot(int pacmanEntityId, int dotEntityId);
		void OnCollisionPacmanBigDot(int pacmanEntityId, int bigDotEntityId);
		void OnCollisionPacmanBlueGhost(int pacmanEntityId, int blueGhostEntityId);
		void OnCollisionPacmanFleeingGhost(int pacmanEntityId, int blueGhostEntityId);
		void OnCollisionPacmanChasingGhost(int pacmanEntityId, int blueGhostEntityId);

		const int m_EntityId;
		function<void(shared_ptr<Event>)> m_Callback;
		const StateContainer* m_StateContainer; // Owner is EntityFactory
		const unordered_map<int, EntityType>* m_EntityIdToType; // Owner is EntityFactory
	};
}