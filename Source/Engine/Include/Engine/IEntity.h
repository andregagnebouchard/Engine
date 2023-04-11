#pragma once
#include <Engine\IComponent.h>
#include <vector>
#include <string>
#include <memory>

using namespace std;
namespace Engine
{
	class IEntity
	{
	public:
		virtual ~IEntity() = default;
		virtual wstring GetName() const = 0;
		virtual vector<shared_ptr<IComponent>> GetComponents() const = 0;
	};
}