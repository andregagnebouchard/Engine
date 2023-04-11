#pragma once
#include "stdafx.h"
#include <Engine/IComponent.h>
#include "Entity.h"
namespace Game
{
	Entity::Entity(const wstring& name, const vector<shared_ptr<Engine::IComponent>>& components) :
		m_Name(name),
		m_Components(components)
	{

	}
	wstring Entity::GetName() const
	{
		return m_Name;
	}

	vector<shared_ptr<Engine::IComponent>> Entity::GetComponents() const
	{
		return m_Components;
	}
}