#pragma once
#include <memory>
#include <string>
#include <vector>
using namespace std;
namespace Engine
{
	class IEntity;
	class IComponentFactory;
	class IEntityFactory
	{
	public:
		virtual ~IEntityFactory() = default;
		virtual shared_ptr<IEntity> CreateEntity(const wstring &name) = 0;
		virtual void RegisterEntity(const vector<wstring> &componentNames, const wstring &entityName) = 0;
		static shared_ptr<IEntityFactory> Create(shared_ptr<IComponentFactory> componentFactory);
	};
}
