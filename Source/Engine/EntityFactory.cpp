#pragma once
#include "EntityFactory.h"
#include "Entity.h"
#include "StringUtil.h"
#include <Engine\IComponentFactory.h>
#include <Engine\IComponent.h>
#include <Engine\ISystemGraphic.h>
#include <Engine\ISystemInput.h>
#include <Engine\ISystemLogic.h>
using namespace std;
namespace Engine
{
	EntityFactory::EntityFactory(shared_ptr<IComponentFactory> componentFactory, shared_ptr<ISystemGraphic> systemGraphic, shared_ptr<ISystemLogic> systemLogic, shared_ptr<ISystemInput> systemInput) :
		m_ComponentFactory(componentFactory),
		m_SystemLogic(systemLogic),
		m_SystemGraphic(systemGraphic),
		m_SystemInput(systemInput),
		m_ComponentId(0)
	{
		if (componentFactory == nullptr) throw invalid_argument("The parameter \"componentFactory\" is nullptr");
		if (systemGraphic == nullptr) throw invalid_argument("The parameter \"systemGraphic\" is nullptr");
		if (systemLogic == nullptr) throw invalid_argument("The parameter \"systemLogic\" is nullptr");
		if (systemInput == nullptr) throw invalid_argument("The parameter \"systemInput\" is nullptr");
	}

	shared_ptr<IEntity> EntityFactory::CreateEntity(const wstring &name)
	{
		// Validate if the entity is already registered
		auto it = m_EntityComponentsMap.find(name);
		if(it == m_EntityComponentsMap.end())
			throw invalid_argument("The entity is not registered :" + StringUtil::ToStr(name));

		// Create all the components associated with the entity using the factory provided by the user
		vector<shared_ptr<IComponent>> components;
		for (const wstring &name : it->second)
		{
			auto component = m_ComponentFactory->Create(name);
			if(component == nullptr)
				throw runtime_error("The component named \"" + StringUtil::ToStr(name) + "\" returned a nullptr from the ComponentFactory provided by the application");

			if (component->GetName() != name)
				throw runtime_error("The component factory did not return the expected component. Asked for \"" + StringUtil::ToStr(name) + "\" but received \"" + StringUtil::ToStr(component->GetName()));

			// Set an unique id for each created component
			component->SetId(m_ComponentId++);
			components.push_back(component);
		}

		// Register the component to its proper system
		for (auto &component : components)
		{
			switch (component->GetType())
			{
			case IComponent::Type::Audio:
				throw "Not implemented";
			case IComponent::Type::Graphic:
				m_SystemGraphic->Add(component);
				break;
			case IComponent::Type::Input:
				m_SystemInput->Add(component);
				break;
			case IComponent::Type::Logic:
				m_SystemLogic->Add(component);
				break;
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
}
