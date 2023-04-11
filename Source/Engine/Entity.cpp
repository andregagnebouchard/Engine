#pragma once
#include "Entity.h"
namespace Engine
{
	Entity::Entity(const wstring &name, const vector<shared_ptr<IComponent>> &components) :
		m_Name(name),
		m_Components(components)
	{

	}
	wstring Entity::GetName() const
	{
		return m_Name;
	}

	vector<shared_ptr<IComponent>> Entity::GetComponents() const
	{
		return m_Components;
	}
}