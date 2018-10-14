#include "stdafx.h"
#include <Engine\IApplication.h>
#include <Engine\IApplicationOption.h>
int main()
{
	auto app = Engine::IApplication::Create();
	auto options = Engine::IApplicationOption::Create();
	options->Load(L"Ressource.xml");

	app->Init(options);
	app->RunLoop();
}