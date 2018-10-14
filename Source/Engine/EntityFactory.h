#pragma once
#include <Engine/IEntityFactory.h>
#include <map>
using namespace std;
namespace Engine
{
	class IEntity;
	class IComponentFactory;
	class EntityFactory : public IEntityFactory
	{
	public:
		EntityFactory(shared_ptr<IComponentFactory> componentFactory);
		virtual ~EntityFactory() = default;
		shared_ptr<IEntity> CreateEntity(const wstring &name) override;
		void RegisterEntity(const vector<wstring> &componentNames, const wstring &entityName) override;
	private:
		shared_ptr<IComponentFactory> m_ComponentFactory;
		map<wstring, vector<wstring>> m_EntityComponentsMap;
	};
}
