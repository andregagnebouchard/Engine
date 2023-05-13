#include "stdafx.h"
#include "SystemLogic.h"
#include "Messager.h"
#include <Engine\IComponent.h>
#include "StringUtil.h"
namespace Engine
{
	SystemLogic::SystemLogic()
	{
	}

	void SystemLogic::Init()
	{
	}

	void SystemLogic::Shutdown()
	{
	}

	void SystemLogic::Update()
	{
		// Update all components
		for (auto &component : m_Components)
			component.second->Update();
	}

	void SystemLogic::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in SystemInput");

		m_Components[component->GetId()] = component;
	}

	void SystemLogic::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it == m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is not in SystemLogic");

		m_Components.erase(component->GetId());
	}
}