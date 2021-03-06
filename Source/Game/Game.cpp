#include "stdafx.h"
#include <Engine\IApplication.h>
#include <Engine\IApplicationOption.h>
#include <Engine\Messager.h>
#include "ComponentFactory.h"
int main()
{
	auto app = Engine::IApplication::Create();
	auto options = Engine::IApplicationOption::Create();
	options->Load(L"Ressource.xml");

	app->Init(options, make_shared<Game::ComponentFactory>());
	Messager::Fire(make_shared<EntityEvent>(Event::Id::CREATE_ENTITY, EntityEvent::Type::Create, L"Mushroom"));
	app->RunLoop();
}