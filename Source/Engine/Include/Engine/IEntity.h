#pragma once
#include <string>
using namespace std;
namespace Engine
{
	// An entity is used as a named collection of components
	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual wstring GetName() const = 0;
	};
}