#pragma once
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	class IComponent;

	// The game project must implement this class and feed it to IEntityFactory
	class IComponentFactory
	{
	public:
		virtual ~IComponentFactory() = default;
		virtual shared_ptr<IComponent> Create(const wstring &name) = 0;
	};
}
