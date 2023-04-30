#pragma once
#include <string>
#include <Engine\IEntity.h>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	// An entity is used as a named collection of components
	class EntityEvent;
	class IEntityFactory
	{
	public:
		virtual ~IEntityFactory() = default;
		virtual shared_ptr<IEntity> Create(shared_ptr<EntityEvent> event) = 0;
		virtual void Delete(int entityId) = 0;
	};
}