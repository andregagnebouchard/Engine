#pragma once
#include <Engine\ISystem.h>
#include <Engine\Typedef.h>
#include <memory>
using namespace std;
namespace Engine
{
	class ISystemGraphic : public ISystem
	{
	public:
		~ISystemGraphic() = default;

		// ISystem
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;

		// ISystemGraphic
		virtual void Resize(uint width, uint height) = 0;
	};
}