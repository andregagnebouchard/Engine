#pragma once
#include <Engine\ISystemLogic.h>
#include <memory>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class SystemLogic : public ISystemLogic
	{
	public:
		SystemLogic() = default;
		~SystemLogic() = default;

		// ISystem
		void Init() override {};
		void Shutdown() override {};
		void Update() override;
		void Add(const shared_ptr<IComponent> component) override;
		void Remove(const shared_ptr<IComponent> component) override;

	private:
		unordered_map<int, shared_ptr<IComponent>> m_Components;
	};
}