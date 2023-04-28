#pragma once
#include <Engine\ISystemPhysic.h>
#include "Messager.h"
#include <unordered_map>
using namespace std;
namespace Engine
{
	class ICollisionLogic;
	class Box2DPhysic;
	class SystemPhysic : public ISystemPhysic
	{
	public:
		SystemPhysic(shared_ptr<ICollisionLogic> collisionLogic, shared_ptr<Box2DPhysic> box2DPhysic);
		~SystemPhysic() = default;

		// ISystem
		void Init() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Add(shared_ptr<IComponent> component) override;
		void Remove(shared_ptr<IComponent> component) override;

	private:
		void CreateEntity(const wstring& entityName);
		void DeleteEntity(const wstring& entityName);
		MessageQueue m_MsgQueue;
		shared_ptr<ICollisionLogic> m_CollisionLogic;
		shared_ptr<Box2DPhysic> m_Box2DPhysic;
		unordered_map<int, shared_ptr<IComponent>> m_Components;
	};
}