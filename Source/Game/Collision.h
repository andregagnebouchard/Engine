#pragma once
#include <Engine\IComponent.h>
#include "Entity.h"
using namespace Engine;
namespace Game
{
	struct StateContainer;
	class CollisionLogicComponent : public IComponent
	{
	public:
		CollisionLogicComponent(int entityId, StateContainer *stateContainer, const unordered_map<int, Entity::Type> *entityIdToType);
		~CollisionLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override {}; // Events are handled synchronously for this one, no need for update

		wstring GetName() const override { return L"CollisionLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		void OnCollision(shared_ptr<Event> event);
		void OnCollisionPacmanSmallDot(int pacmanEntityId, int dotEntityId);
		void OnCollisionPacmanBigDot(int pacmanEntityId, int bigDotEntityId);
		void OnColisionPacmanBlueGhost(int pacmanEntityId, int blueGhostEntityId);
		void OnCollisionPacmanFleeingGhost(int pacmanEntityId, int blueGhostEntityId);
		void OnCollisionPacmanChasingGhost(int pacmanEntityId, int blueGhostEntityId);

		int m_EntityId;
		function<void(shared_ptr<Event>)> m_Callback;
		StateContainer* m_StateContainer; // Owner is EntityFactory
		const unordered_map<int, Entity::Type>* m_EntityIdToType; // Owner is EntityFactory
	};
}