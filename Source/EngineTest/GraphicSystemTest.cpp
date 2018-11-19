#include <gtest\gtest.h>
#include <Engine\Messager.h>
#include <Engine\SystemGraphic.h>
#include <Engine\ResourceCache.h>
#include <Engine\Window.h>
#include <Engine\StringUtil.h>
#include <Engine\IComponent.h>
#include <gmock\gmock.h>
using namespace Engine;
//=================================================================================================
class GraphicSystemTest : public testing::Test
{
protected:

  const wstring RESOURCE_NAME = L"Square";

  GraphicSystemTest()
  {
    m_Sprite = make_shared<Resource>(L"..\\..\\Support\\Testing\\ResourceCacheTest\\BLACK_SQUARE_10x9.png", RESOURCE_NAME);
    m_ResourceCache = make_shared<ResourceCache>();
    m_ResourceCache->AddResource(m_Sprite);
		m_RenderWindow = make_shared<sf::RenderWindow>(sf::VideoMode(1, 1), sf::String("Engine"));
		m_Window = make_shared<Window>(m_RenderWindow);

    m_Graphic = make_shared<SystemGraphic>(m_RenderWindow, m_Window, m_ResourceCache);
    m_Graphic->Init();
  }

  ~GraphicSystemTest()
  {
    m_Graphic->Shutdown();
  }
  shared_ptr<Resource> m_Sprite;
  shared_ptr<ResourceCache> m_ResourceCache;
  shared_ptr<sf::RenderWindow> m_RenderWindow;
	shared_ptr<IWindow> m_Window;
  shared_ptr<SystemGraphic> m_Graphic;

};

class GraphicComponentMock : public IComponent
{
public:
	MOCK_METHOD0(Init, void());
	MOCK_METHOD0(Shutdown, void());
	MOCK_METHOD1(Update, void(float dt));

	MOCK_CONST_METHOD0(GetName, wstring());	

	IComponent::Type GetType() const override { return IComponent::Type::Graphic; };
private:

};

//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateOnValidSpriteRenderEvent)
{
	Messager::Fire(make_shared<RenderEvent>(Event::Id::RENDER_SPRITE, RESOURCE_NAME));
	m_Graphic->Update(0);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateOnInvalidSpriteRenderEvent)
{
  Messager::Fire(make_shared<RenderEvent>(Event::Id::RENDER_SPRITE, L""));
  EXPECT_THROW(m_Graphic->Update(0), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateOnNoEvent)
{
  m_Graphic->Update(0);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicAddValidComponent)
{
	m_Graphic->Add(make_shared<GraphicComponentMock>());
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicAddInvalidComponent)
{
	EXPECT_THROW(m_Graphic->Add(nullptr); , invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicRemoveComponent)
{
	auto component = make_shared<GraphicComponentMock>();
	m_Graphic->Add(component);
	m_Graphic->Remove(component);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicRemoveComponentNotAdded)
{
	auto component = make_shared<GraphicComponentMock>();
	EXPECT_THROW(m_Graphic->Remove(component);, invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicAddComponentTwice)
{
	auto component = make_shared<GraphicComponentMock>();
	m_Graphic->Add(component);
	EXPECT_THROW(m_Graphic->Add(component); , invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateAllComponentOnUpdate)
{
	auto component = make_shared<GraphicComponentMock>();
	m_Graphic->Add(component);
	m_Graphic->Update(0);
	EXPECT_CALL(*component, Update(::testing::_)).Times(::testing::AtLeast(1));
}