#include <gtest\gtest.h>
#include <Engine\Include\Engine\GraphicSystem.h>
//=================================================================================================
class GraphicSystemTest : public testing::Test
{
protected:

  virtual void SetUp()
  {
    m_Graphic->Init();
  }

  virtual void TearDown()
  {
    m_Graphic->Shutdown();
  }

  shared_ptr<Engine::GraphicSystem> m_Graphic = Engine::GraphicSystem::Create(Engine::WindowInfo{ 800, 600, "Graphic" });
};
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindow)
{
  m_Graphic->Resize(1920, 1080);
}
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindowWithZeroWidth)
{
  EXPECT_THROW(m_Graphic->Resize(0, 1080), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindowWithZeroHeight)
{
  EXPECT_THROW(m_Graphic->Resize(1920, 0), invalid_argument);
}
//=================================================================================================
TEST_F(GraphicSystemTest, ResizeGraphicSystemWindowWithTooBigResolution)
{
  EXPECT_THROW(m_Graphic->Resize(1921, 1081), invalid_argument);
}
//=================================================================================================