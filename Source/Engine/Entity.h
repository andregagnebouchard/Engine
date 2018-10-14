#pragma once
#include <Engine/IEntity.h>
#include <memory>
#include <vector>
namespace Engine
{
	class IComponent;
	class Entity : public IEntity
	{
	public:
		Entity(const wstring &name, const vector<shared_ptr<IComponent>> &components);
		~Entity() = default;
		wstring GetName() const override;
	private:
		vector<shared_ptr<IComponent>> m_Components;
		wstring m_Name;

	};
}