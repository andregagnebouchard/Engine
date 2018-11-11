#pragma once
#include <Engine\ISystem.h>
#include <Engine\Typedef.h>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	class IComponent;
	class ISystemLogic : public ISystem
	{
	public:
		~ISystemLogic() = default;

		// ISystem
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
		virtual void Add(shared_ptr<IComponent> component) = 0;
	};
}