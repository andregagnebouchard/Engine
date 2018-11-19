#include "stdafx.h"
#include "System.h"
#include <Engine\IComponent.h>
#include "StringUtil.h"
namespace Engine
{
	void System::Add(shared_ptr<IComponent> component)
	{
		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in system");

		m_Components[component->GetId()] = component;
	}
	void System::Remove(shared_ptr<IComponent> component)
	{

	}
}