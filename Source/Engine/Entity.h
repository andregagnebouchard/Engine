#pragma once
#include <Engine\IComponent.h>
#include <vector>
#include <string>
#include <memory>
using namespace std;
namespace Engine
{
	class IComponent;
	class Entity
	{
	public:
		Entity(const wstring &name, const vector<shared_ptr<IComponent>> &components);
		~Entity() = default;
		wstring GetName() const { return m_Name; };
		vector<shared_ptr<IComponent>> GetComponents() const { return m_Components; };
	private:
		vector<shared_ptr<IComponent>> m_Components;
		wstring m_Name;
	};
}