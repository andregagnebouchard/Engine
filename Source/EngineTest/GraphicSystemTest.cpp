#include <gtest\gtest.h>
#include <Engine\Messager.h>
#include <Engine\SystemGraphic.h>
using namespace Engine;
//=================================================================================================
class GraphicSystemTest : public testing::Test
{
protected:

  virtual void SetUp()
  {
    m_Graphic->Init();
    m_Graphic->SetWindowVisible(false); // For optimization purposes
  }

  virtual void TearDown()
  {
    m_Graphic->Shutdown();
  }

	shared_ptr<sf::Window> m_Window = make_shared<sf::Window>(sf::VideoMode(1024, 768), sf::String("Engine"));
  shared_ptr<SystemGraphic> m_Graphic = make_shared<SystemGraphic>(m_Window);
};
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindow)
{
  m_Graphic->ResizeWindow(1920, 1080);
}
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindowWithZeroWidth)
{
  EXPECT_THROW(m_Graphic->ResizeWindow(0, 1080), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindowWithZeroHeight)
{
  EXPECT_THROW(m_Graphic->ResizeWindow(1920, 0), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindowWithTooBigResolution)
{
  EXPECT_THROW(m_Graphic->ResizeWindow(1921, 1081), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, SystemGraphicAttachedOnRenderEvent)
{
	Event event(Event::Type::Rendering, Event::Id::RENDER_SPRITE);
	event.render.spriteId = 0;
	Messager::Fire(event);
	m_Graphic->Update(0);
}
//=================================================================================================