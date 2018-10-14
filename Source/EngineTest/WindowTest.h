#include <gtest\gtest.h>
#include <Engine\Window.h>
using namespace Engine;
//=================================================================================================
class WindowTest : public testing::Test
{
protected:

	WindowTest()
	{
	}

	~WindowTest()
	{
	}
	shared_ptr<IWindow> m_Window = make_shared<Window>(sf::VideoMode(1, 1), "TestWindow");

};
//=================================================================================================
TEST_F(WindowTest, ResizeGraphicSystemWindow)
{
	m_Window->Resize(1920, 1080);
}
//=================================================================================================
TEST_F(WindowTest, ResizeGraphicSystemWindowWithZeroWidth)
{
	EXPECT_THROW(m_Window->Resize(0, 1080), invalid_argument);
}
//=================================================================================================
TEST_F(WindowTest, ResizeGraphicSystemWindowWithZeroHeight)
{
	EXPECT_THROW(m_Window->Resize(1920, 0), invalid_argument);
}
//=================================================================================================
TEST_F(WindowTest, ResizeGraphicSystemWindowWithTooBigResolution)
{
	EXPECT_THROW(m_Window->Resize(1921, 1081), invalid_argument);
}
//=================================================================================================