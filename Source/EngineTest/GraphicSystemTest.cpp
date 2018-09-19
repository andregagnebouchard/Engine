#include <gtest\gtest.h>
#include <Engine\Messager.h>
#include <Engine\SystemGraphic.h>
#include <Engine\ResourceCache.h>
#include <Engine\StringUtil.h>
using namespace Engine;
//=================================================================================================
class GraphicSystemTest : public testing::Test
{
protected:

  const string RESOURCE_NAME = "Square";

  GraphicSystemTest()
  {
    m_Sprite = make_shared<Resource>(L"..\\..\\Support\\Testing\\ResourceCacheTest\\BLACK_SQUARE_10x9.png", StringUtil::ToWStr(RESOURCE_NAME));
    m_ResourceCache = make_shared<ResourceCache>();
    m_ResourceCache->AddResource(m_Sprite);
    m_Window = make_shared<sf::RenderWindow>(sf::VideoMode(1, 1), sf::String("Engine"));
    m_Graphic = make_shared<SystemGraphic>(m_Window, m_ResourceCache);
    m_Graphic->Init();
  }

  ~GraphicSystemTest()
  {
    m_Graphic->Shutdown();
  }
  shared_ptr<Resource> m_Sprite;
  shared_ptr<ResourceCache> m_ResourceCache;
  shared_ptr<sf::RenderWindow> m_Window;
  shared_ptr<SystemGraphic> m_Graphic;

};
//=================================================================================================
TEST_F(GraphicSystemTest, DISABLED_ResizeGraphicSystemWindow)
{
  m_Graphic->ResizeWindow(1920, 1080);
}
//=================================================================================================
TEST_F(GraphicSystemTest, DISABLED_ResizeGraphicSystemWindowWithZeroWidth)
{
  EXPECT_THROW(m_Graphic->ResizeWindow(0, 1080), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, DISABLED_ResizeGraphicSystemWindowWithZeroHeight)
{
  EXPECT_THROW(m_Graphic->ResizeWindow(1920, 0), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, DISABLED_ResizeGraphicSystemWindowWithTooBigResolution)
{
  EXPECT_THROW(m_Graphic->ResizeWindow(1921, 1081), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateOnValidSpriteRenderEvent)
{
	Event event(Event::Type::Rendering, Event::Id::RENDER_SPRITE);
  strcpy_s(event.render.resourceName, RESOURCE_NAME.c_str());
	Messager::Fire(event);
	m_Graphic->Update(0);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateOnInvalidSpriteRenderEvent)
{
  const string invalidResource = "";
  Event event(Event::Type::Rendering, Event::Id::RENDER_SPRITE);
  strcpy_s(event.render.resourceName, invalidResource.c_str());
  Messager::Fire(event);
  EXPECT_THROW(m_Graphic->Update(0), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicUpdateOnNoEvent)
{
  m_Graphic->Update(0);
}
//=================================================================================================