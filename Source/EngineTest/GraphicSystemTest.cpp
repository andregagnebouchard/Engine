#include <gtest\gtest.h>
#include <Engine\Messager.h>
#include <Engine\SystemGraphic.h>
#include <Engine\ResourceCache.h>
#include <Engine\Window.h>
#include <Engine\StringUtil.h>
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