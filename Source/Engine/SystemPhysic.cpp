#include "stdafx.h"
#include "SystemPhysic.h"
#include "Messager.h"
#include <Engine\IComponent.h>
#include "StringUtil.h"
namespace Engine
{
	SystemPhysic::SystemPhysic(shared_ptr<ICollisionLogic> collisionLogic) : 
		m_CollisionLogic(collisionLogic)
	{
	}

	void SystemPhysic::Init()
	{
	}

	void SystemPhysic::Shutdown()
	{
	}

	void SystemPhysic::Update(float dt)
	{
		// Update all components
		for (auto& component : m_Components)
			component.second->Update(dt);
	}

	void SystemPhysic::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in SystemPhysic");

		m_Components[component->GetId()] = component;
	}

	void SystemPhysic::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it == m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is not in SystemLogic");

		m_Components.erase(component->GetId());
	}
}