#pragma once
#include <string>
#include <Engine\Entity.h>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	// An entity is used as a named collection of components
	class EntityEvent;
	class IGameEntityFactory
	{
	public:
		virtual ~IGameEntityFactory() = default;
		virtual shared_ptr<Entity> Create(shared_ptr<EntityEvent> event) = 0;
		virtual void Delete(int entityId) = 0;
	};
}