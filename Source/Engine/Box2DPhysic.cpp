#include "stdafx.h"
#include <Box2D/Box2D.h>
#include "Box2DPhysic.h"
namespace Engine
{
	Box2DPhysic::Box2DPhysic() : 
		m_Gravity(0.0f, 0.0f),
		m_World(m_Gravity)
	{
	}

	void Box2DPhysic::Create()
	{
		b2BodyDef groundBodyDef; // Hold data to construct a rigid body. Static body by default
		groundBodyDef.position.Set(0.0f, -10.0f);

		b2Body* groundBody = m_World.CreateBody(&groundBodyDef); // Rigid body. We own that pointer

		b2PolygonShape groundBox;
		groundBox.SetAsBox(1.0f, 1.0f);

		b2Fixture* fixture = groundBody->CreateFixture(&groundBox, 0.0f); // Bind the shape to the rigid body
	}
}