#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;
namespace Engine
{
	class IEntity;
	class IComponentFactory;
	class EntityFactory
	{
	public:
		EntityFactory(shared_ptr<IComponentFactory> componentFactory);
		shared_ptr<IEntity> CreateEntity(const wstring &name);
		void RegisterEntity(const vector<wstring> &componentNames, const wstring &entityName);
	private:
		shared_ptr<IComponentFactory> m_ComponentFactory;
		map<wstring, vector<wstring>> m_EntityComponentsMap;
	};
}
