#pragma once
#include <Engine\ISystemPhysic.h>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class ICollisionLogic;
	class SystemPhysic : public ISystemPhysic
	{
	public:
		SystemPhysic(shared_ptr<ICollisionLogic> collisionLogic);
		~SystemPhysic() = default;

		// ISystem
		void Init() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Add(shared_ptr<IComponent> component) override;
		void Remove(shared_ptr<IComponent> component) override;

	private:
		shared_ptr<ICollisionLogic> m_CollisionLogic;
		unordered_map<int, shared_ptr<IComponent>> m_Components;
	};
}