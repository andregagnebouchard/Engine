#include <gtest\gtest.h>
#include <GL\glew.h>
#include <GL\GL.h>
TEST(glewTest, CanUseGlew)
{
	glewInit();
}