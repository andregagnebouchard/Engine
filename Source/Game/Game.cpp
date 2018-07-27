#include "stdafx.h"
#include <Engine\ISystemGraphic.h>
int main()
{
	Engine::WindowInfo windowInfo{ 640, 480, "Hello" };
	auto graphic = Engine::ISystemGraphic::Create(windowInfo);
	graphic->Init();
}