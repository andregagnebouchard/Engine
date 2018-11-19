#pragma once
#include <Engine\ISystem.h>
#include <map>
using namespace std;
namespace Engine
{
	class System : public ISystem
	{
	public:
		virtual ~System() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;

		// Implement this once for all systems
		void Add(shared_ptr<IComponent> component) override;
		void Remove(shared_ptr<IComponent> component) override;
	protected:
		map<int, shared_ptr<IComponent>> m_Components;
	};
}