#include "stdafx.h"
#include <Engine\IApplication.h>
#include <Engine\IApplicationOption.h>
#include <Engine\Messager.h>
#include <Engine\EventDefinition.h>
#include "EntityFactory.h"

class Animal
{
public:
	virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
	virtual ~Dog() = default;
	int dogName = 5;
};
int main()
{
	Dog dog;
	Animal* ptr = &dog;
	Dog* myDog = dynamic_cast<Dog*>(ptr);
	auto app = Engine::IApplication::Create();
	auto options = Engine::IApplicationOption::Create();
	options->Load(L"Ressource.xml");

	app->Init(options, make_shared<Game::EntityFactory>());
	Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Mushroom"));
	app->RunLoop();
}