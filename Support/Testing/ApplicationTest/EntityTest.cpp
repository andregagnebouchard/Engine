#include <gtest\gtest.h>
#include <Engine/EntityFactory.h>
#include <Engine/IComponentFactory.h>
#include <Engine/IEntity.h>
#include <Engine/IComponent.h>
#include <Engine/ISystemGraphic.h>
#include <Engine/ISystemLogic.h>
#include <Engine/ISystemInput.h>
#include <gmock\gmock.h>
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

class SystemGraphicMock : public ISystemGraphic
{
public:
	MOCK_METHOD0(Init, void());
	MOCK_METHOD0(Shutdown, void());
	MOCK_METHOD1(Update, void(float dt));
	MOCK_METHOD1(Add, void(shared_ptr<IComponent> component));
	MOCK_METHOD1(Remove, void(shared_ptr<IComponent> component));

	// ISystemGraphic
	MOCK_CONST_METHOD0(GetWindow, shared_ptr<IWindow>());
};

class SystemLogicMock : public ISystemLogic
{
	MOCK_METHOD0(Init, void());
	MOCK_METHOD0(Shutdown, void());
	MOCK_METHOD1(Update, void(float dt));
	MOCK_METHOD1(Add, void(shared_ptr<IComponent> component));
	MOCK_METHOD1(Remove, void(shared_ptr<IComponent> component));
};

class SystemInputMock : public ISystemInput
{
	MOCK_METHOD0(Init, void());
	MOCK_METHOD0(Shutdown, void());
	MOCK_METHOD1(Update, void(float dt));
	MOCK_METHOD1(Add, void(shared_ptr<IComponent> component));
	MOCK_METHOD1(Remove, void(shared_ptr<IComponent> component));
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
	EXPECT_THROW(EntityFactory(nullptr, make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>()), invalid_argument);
}

TEST(EntityTest, CreateEntityFactoryWithNullSystemGraphic)
{
	EXPECT_THROW(EntityFactory(make_shared<ComponentFactory>(), nullptr, make_shared<SystemLogicMock>(), make_shared<SystemInputMock>()), invalid_argument);
}

TEST(EntityTest, CreateEntityFactoryWithNullSystemLogic)
{
	EXPECT_THROW(EntityFactory(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), nullptr, make_shared<SystemInputMock>()), invalid_argument);
}

TEST(EntityTest, CreateEntityFactoryWithNullSystemInput)
{
	EXPECT_THROW(EntityFactory(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), nullptr), invalid_argument);
}

TEST(EntityTest, CreateEntityFactory)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
}

TEST(EntityTest, RegisterEntity)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
	factory->RegisterEntity({}, ENTITY_NAME);
}

TEST(EntityTest, RegisterSameEntityTwice)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
	factory->RegisterEntity({}, ENTITY_NAME);
	EXPECT_THROW(factory->RegisterEntity({}, ENTITY_NAME), invalid_argument);
}

TEST(EntityTest, CreateUnregisteredEntity)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
	EXPECT_THROW(factory->CreateEntity(ENTITY_NAME), invalid_argument);
}

TEST(EntityTest, CreateRegisteredEntity)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
	factory->RegisterEntity({}, ENTITY_NAME);
	auto entity = factory->CreateEntity(ENTITY_NAME);
	ASSERT_EQ(entity->GetName(), ENTITY_NAME);
}

TEST(EntityTest, CreateRegisteredEntityWithExistingComponent)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
	factory->RegisterEntity({ EXISTING_COMPONENT }, ENTITY_NAME);
	auto entity = factory->CreateEntity(ENTITY_NAME);
	ASSERT_EQ(entity->GetName(), ENTITY_NAME);
}

TEST(EntityTest, CreateRegisteredEntityWithNonExistingComponent)
{
	auto factory = make_shared<EntityFactory>(make_shared<ComponentFactory>(), make_shared<SystemGraphicMock>(), make_shared<SystemLogicMock>(), make_shared<SystemInputMock>());
	factory->RegisterEntity({ NON_EXISTING_COMPONENT }, ENTITY_NAME);
	EXPECT_THROW(auto entity = factory->CreateEntity(ENTITY_NAME), runtime_error);
}