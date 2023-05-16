#include "stdafx.h"
#include <Engine\Application.h>
#include <Engine\ApplicationOption.h>
#include <Engine\Messager.h>
#include <Engine\EventDefinition.h>
#include "EntityFactory.h"
#include "Engine\Grid.h"
#include "Engine\EntityIdCounter.h"
#include "Engine\MathStructs.h"

int main()
{
	auto options = make_shared<Engine::ApplicationOption>();
	options->Load(L"Ressource.xml");
	auto app = make_shared<Engine::Application>();

	app->Init(options, make_shared<Game::EntityFactory>());

	// Grid must be the first component created, as it listens to the other entity creation events
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Grid", EntityIdCounter::GenerateEntityId(), nullptr));
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"LevelGenerator", EntityIdCounter::GenerateEntityId(), nullptr));
	app->RunLoop();
}