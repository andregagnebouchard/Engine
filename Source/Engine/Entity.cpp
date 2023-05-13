#pragma once
#include "stdafx.h"
#include "Entity.h"
namespace Engine
{
	Entity::Entity(const wstring &name, const vector<shared_ptr<IComponent>> &components) :
		m_Name(name),
		m_Components(components)
	{
	}
}