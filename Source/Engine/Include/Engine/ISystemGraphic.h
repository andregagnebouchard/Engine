#pragma once
#include <Engine\ISystem.h>
#include <Engine\Typedef.h>
#include <memory>
using namespace std;
namespace Engine
{
	class IWindow;
	class ISystemGraphic : public ISystem
	{
	public:
		~ISystemGraphic() = default;

		// ISystem
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;

		// ISystemGraphic
		virtual shared_ptr<IWindow> GetWindow() const = 0;
	};
}