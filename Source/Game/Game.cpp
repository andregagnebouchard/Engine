#include "stdafx.h"
#include <Engine\IApplication.h>
int main()
{
	auto app = Engine::IApplication::Create();
	app->Init();
	app->RunLoop();
}