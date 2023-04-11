#pragma once
#include <Engine\IEntityFactory.h>
#include <Engine\IEntity.h>
#include <memory>
#include <string>
using namespace std;
namespace Game
{
	class EntityFactory : public Engine::IEntityFactory
	{
	public:
		~EntityFactory() = default;
		shared_ptr<Engine::IEntity> Create(const wstring& name) override;
	};
}
