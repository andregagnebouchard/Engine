#pragma once
#include <Engine/IEntity.h>
#include <memory>
#include <vector>
namespace Game
{
	class Engine::IComponent;
	class Entity : public Engine::IEntity
	{
	public:
		enum Type
		{
			Pacman,
			Pause
		};

		Entity(const wstring& name, const vector<shared_ptr<Engine::IComponent>>& components);
		~Entity() = default;
		wstring GetName() const override;
		vector<shared_ptr<Engine::IComponent>> GetComponents() const override;
	private:
		vector<shared_ptr<Engine::IComponent>> m_Components;
		wstring m_Name;
	};
}