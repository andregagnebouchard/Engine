#include "stdafx.h"
#include <Engine\Typedef.h>
#include <Engine\GraphicSystem.h>
int main()
{
	Engine::WindowInfo windowInfo{ 640, 480, "Hello" };
	auto graphic = Engine::GraphicSystem::Create(windowInfo);
	graphic->Init();
}