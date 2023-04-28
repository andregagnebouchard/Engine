#pragma once
using namespace std;
#include <Box2D/Box2D.h>
namespace Engine
{
	class Box2DPhysic
	{
	public:
		Box2DPhysic();
		~Box2DPhysic() = default;

		b2World* GetWorld() { return &m_World; };
		void Create();
	private:
		b2World m_World;
		b2Vec2 m_Gravity;
	};
}