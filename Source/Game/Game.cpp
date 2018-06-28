#include "stdafx.h"
#include <Engine\IGraphicSystem.h>
int main()
{
	Engine::WindowInfo windowInfo{ 640, 480, "Hello" };
	auto graphic = Engine::IGraphicSystem::Create(windowInfo);
	graphic->Init();
}