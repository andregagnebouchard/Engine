#include <gtest\gtest.h>
#include <Engine/EntityFactory.h>
#include <Engine/IComponentFactory.h>
#include <Engine/IEntity.h>
#include <Engine/IComponent.h>
#include <Engine/ISystemGraphic.h>
#include <Engine/ISystemLogic.h>
#include <Engine/ISystemInput.h>
using namespace Engine;
using namespace std;

const wstring EXISTING_COMPONENT = L"ValidComponent";
const wstring NON_EXISTING_COMPONENT = L"NonExistingComponent";
const wstring ENTITY_NAME = L"Entity1";
class ValidComponent : public IComponent
{
	void Init() override {}
	void Shutdown() override {}
	void Update(float dt) override {}

	wstring GetName() const
	{
		return L"ValidComponent";
	}
	Type GetType() const
	{
		return IComponent::Type::Graphic;
	}
};

// Mocks
class SystemGraphic : public ISystemGraphic
{
public:
	void Init() override {};
	void Shutdown() override {};
	void Update(float dt) override {};
	void Add(shared_ptr<IComponent> component) override {};

	// ISystemGraphic
	shared_ptr<IWindow> GetWindow() const override { return nullptr; };
};

class SystemLogic : public ISystemLogic
{
	void Init() override {};
	void Shutdown() override {};
	void Update(float dt) override {};
	void Add(shared_ptr<IComponent> component) override {};
};

class SystemInput : public ISystemInput
{
	void Init() override {};
	void Shutdown() override {};
	void Update(float dt) override {};
	void Add(shared_ptr<IComponent> component) override {};
};
class ComponentFactory : public IComponentFactory
{
public:
	shared_ptr<IComponent> Create(const wstring &name) override
	{
		if (name == EXISTING_COMPONENT)
			return make_shared<ValidComponent>();

		return nullptr;
	}
};

TEST(EntityTest, CreateEntityFactoryWithNullComponentFactory)
{
	EXPECT_THROW(EntityFactory(nullptr, make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>()), invalid_argument);
}

TEST(EntityTest, CreateEntityFactoryWithNullSystemGraphic)
{
	EXPECT_THROW(EntityFactory(make_shared<ComponentFactory>(), nullptr, make_shared<SystemLogic>(), make_shared<SystemInput>()), invalid_argument);
}

TEST(EntityTest, CreateEntityFactoryWithNullSystemLogic)
{
	EXPECT_THROW(EntityFactory(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), nullptr, make_shared<SystemInput>()), invalid_argument);
}

TEST(EntityTest, CreateEntityFactoryWithNullSystemInput)
{
	EXPECT_THROW(EntityFactory(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), nullptr), invalid_argument);
}

TEST(EntityTest, CreateEntityFactory)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
}

TEST(EntityTest, RegisterEntity)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
	factory->RegisterEntity({}, ENTITY_NAME);
}

TEST(EntityTest, RegisterSameEntityTwice)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
	factory->RegisterEntity({}, ENTITY_NAME);
	EXPECT_THROW(factory->RegisterEntity({}, ENTITY_NAME), invalid_argument);
}

TEST(EntityTest, CreateUnregisteredEntity)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
	EXPECT_THROW(factory->CreateEntity(ENTITY_NAME), invalid_argument);
}

TEST(EntityTest, CreateRegisteredEntity)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
	factory->RegisterEntity({}, ENTITY_NAME);
	auto entity = factory->CreateEntity(ENTITY_NAME);
	ASSERT_EQ(entity->GetName(), ENTITY_NAME);
}

TEST(EntityTest, CreateRegisteredEntityWithExistingComponent)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
	factory->RegisterEntity({ EXISTING_COMPONENT }, ENTITY_NAME);
	auto entity = factory->CreateEntity(ENTITY_NAME);
	ASSERT_EQ(entity->GetName(), ENTITY_NAME);
}

TEST(EntityTest, CreateRegisteredEntityWithNonExistingComponent)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphic>(), make_shared<SystemLogic>(), make_shared<SystemInput>());
	factory->RegisterEntity({ NON_EXISTING_COMPONENT }, ENTITY_NAME);
	EXPECT_THROW(auto entity = factory->CreateEntity(ENTITY_NAME), runtime_error);
}