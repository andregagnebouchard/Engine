#pragma once
#include "EntityFactory.h"
#include "Entity.h"
#include "StringUtil.h"
#include <Engine\IComponentFactory.h>
#include <Engine\IComponent.h>
using namespace std;
namespace Engine
{
	EntityFactory::EntityFactory(shared_ptr<IComponentFactory> componentFactory) :
		m_ComponentFactory(componentFactory)
	{

	}
	shared_ptr<IEntity> EntityFactory::CreateEntity(const wstring &name)
	{
		// Validate the entity is already registered
		auto it = m_EntityComponentsMap.find(name);
		if(it == m_EntityComponentsMap.end())
			throw invalid_argument("The entity is not registered :" + StringUtil::ToStr(name));

		// Create all the components associated with the entity using the factory provided by the user
		vector<shared_ptr<IComponent>> components;
		for (const wstring &name : it->second)
		{
			auto component = m_ComponentFactory->Create(name);
			if (component->GetName() != name)
				throw runtime_error("The component factory did not return the expected component. Asked for \"" + StringUtil::ToStr(name) + "\" but received \"" + StringUtil::ToStr(component->GetName()));

			components.push_back(component);
		}

		// Register the component to its proper system
		for (auto &component : components)
		{
			switch (component->GetType())
			{
			case IComponent::Type::Audio:
			case IComponent::Type::Graphic:
			case IComponent::Type::Input:
			default:
				throw runtime_error("Unknown component type");
			}
		}
		return make_shared<Entity>(name, components);
	}
	void EntityFactory::RegisterEntity(const vector<wstring> &componentNames, const wstring &entityName)
	{
		if (m_EntityComponentsMap.find(entityName) != m_EntityComponentsMap.end())
			throw invalid_argument("The entity is already registered :" + StringUtil::ToStr(entityName));

		m_EntityComponentsMap[entityName] = componentNames;
	}

	shared_ptr<IEntityFactory> IEntityFactory::Create(shared_ptr<IComponentFactory> componentFactory)
	{
		if (componentFactory == nullptr)
			throw invalid_argument("The component factory is nullptr");

		return make_shared<EntityFactory>(componentFactory);
	}
}
