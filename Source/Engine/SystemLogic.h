#pragma once
#include <Engine\ISystemLogic.h>
using namespace std;
namespace Engine
{
	class SystemLogic : public ISystemLogic
	{
	public:
		SystemLogic();
		~SystemLogic() = default;

		// ISystem
		void Init() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Add(shared_ptr<IComponent> component) override;

	private:
	};
}