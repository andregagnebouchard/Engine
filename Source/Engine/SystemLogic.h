#pragma once
#include <Engine/IComponent.h>
#include <memory>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class SystemLogic
	{
	public:
		SystemLogic() = default;
		~SystemLogic() = default;

		void Update();
		void Add(const shared_ptr<IComponent> component);
		void Remove(const shared_ptr<IComponent> component);

	private:
		unordered_map<int, shared_ptr<IComponent>> m_Components;
	};
}