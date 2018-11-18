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

	void SystemLogic::Update(float dt)
	{
	}

	void SystemLogic::Add(shared_ptr<IComponent> component)
	{
		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in SystemInput");

		m_Components[component->GetId()] = component;
	}
}