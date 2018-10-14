#pragma once
using namespace std;
#include <string>
namespace Engine
{
	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual wstring GetName() const = 0;

	};
}