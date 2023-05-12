#include "stdafx.h"
#include <Engine\IApplication.h>
#include <Engine\IApplicationOption.h>
#include <Engine\Messager.h>
#include <Engine\EventDefinition.h>
#include "EntityFactory.h"
#include "Engine\WorldGrid.h"
#include "Engine\EntityIdCounter.h"
#include "Engine\math.h"

int main()
{
	auto app = Engine::IApplication::Create();
	auto options = Engine::IApplicationOption::Create();
	options->Load(L"Ressource.xml");

	app->Init(options, make_shared<Game::EntityFactory>());

	// Grid must be the first component created, as it listens to the other entity creation events
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Grid", EntityIdCounter::GenerateEntityId(), nullptr));
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"LevelGenerator", EntityIdCounter::GenerateEntityId(), nullptr));
	app->RunLoop();
}