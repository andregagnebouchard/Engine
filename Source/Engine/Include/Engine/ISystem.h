#pragma once
#include <memory>
namespace Engine
{
	class IComponent;
	class ISystem
	{
	public:
		virtual ~ISystem() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;
		virtual void Add(const shared_ptr<IComponent> component) = 0;
		virtual void Remove(const shared_ptr<IComponent> component) = 0;
	};
}