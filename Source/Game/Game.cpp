#include "stdafx.h"
#include <Engine\IApplication.h>
#include <Engine\IApplicationOption.h>
int main()
{
	auto app = Engine::IApplication::Create();
	app->Init(Engine::IApplicationOption::Create());
	app->RunLoop();
}