#pragma once
#include <Engine\ICollisionLogic.h>
#include <memory>
#include <string>
using namespace std;
namespace Game
{
	class CollisionLogic : public Engine::ICollisionLogic
	{
	public:
		~CollisionLogic() = default;
	};
}
