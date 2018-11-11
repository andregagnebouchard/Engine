#pragma once
#include <Engine\IComponentFactory.h>
using namespace Engine;
namespace Game
{
	class ComponentFactory : public IComponentFactory
	{
	public:
		shared_ptr<IComponent> Create(const wstring &name) override;
	};
}