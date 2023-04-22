#include "stdafx.h"
#include <Engine\IApplication.h>
#include <Engine\IApplicationOption.h>
#include <Engine\Messager.h>
#include <Engine\EventDefinition.h>
#include "EntityFactory.h"
#include "CollisionLogic.h"

int main()
{
	auto app = Engine::IApplication::Create();
	auto options = Engine::IApplicationOption::Create();
	options->Load(L"Ressource.xml");

	app->Init(options, make_shared<Game::EntityFactory>(), make_shared<Game::CollisionLogic>());
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Pacman"));
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Pause"));
	app->RunLoop();
}