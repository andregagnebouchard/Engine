#include "stdafx.h"
#include "SystemLogic.h"
#include <Engine\IComponent.h>
namespace Engine
{
	void SystemLogic::Update()
	{
		// Update all components
		for (const auto &component : m_Components)
			component.second->Update();
	}

	void SystemLogic::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.emplace(component->GetId(), component);
	}

	void SystemLogic::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.erase(component->GetId());
	}
}