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
	class ISystemGraphic;
	class ISystemLogic;
	class ISystemInput;
	class EntityFactory
	{
	public:
		// The systems are required to register in order to register the components to them
		EntityFactory(shared_ptr<IComponentFactory> componentFactory, shared_ptr<ISystemGraphic> systemGraphic, shared_ptr<ISystemLogic> systemLogic, shared_ptr<ISystemInput> systemInput);

		shared_ptr<IEntity> CreateEntity(const wstring &name);
		void RegisterEntity(const vector<wstring> &componentNames, const wstring &entityName);
	private:
		shared_ptr<IComponentFactory> m_ComponentFactory;
		map<wstring, vector<wstring>> m_EntityComponentsMap;
		shared_ptr<ISystemGraphic> m_SystemGraphic;
		shared_ptr<ISystemLogic> m_SystemLogic;
		shared_ptr<ISystemInput> m_SystemInput;
		int m_ComponentId;
	};
}
