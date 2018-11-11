#pragma once
#include <string>
using namespace std;
namespace Engine
{
	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual wstring GetName() const = 0;
	};
}