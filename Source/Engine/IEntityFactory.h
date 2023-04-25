#pragma once
#include <string>
#include <Engine\IEntity.h>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	// An entity is used as a named collection of components
	class IEntityFactory
	{
	public:
		virtual ~IEntityFactory() = default;
		virtual shared_ptr<IEntity> Create(const wstring & name, int entityId) = 0;
		virtual void Delete(int entityId) = 0;
	};
}