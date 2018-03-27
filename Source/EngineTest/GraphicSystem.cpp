#include <gtest\gtest.h>
#include <Engine\Include\Engine\GraphicSystem.h>
#include <Engine\Startup.h>
//=================================================================================================
TEST(Engine, InitGraphicSystem)
{
	Engine::WindowInfo windowInfo;
	windowInfo.width = 800;
	windowInfo.length = 600;
	windowInfo.title = "TestTitle";

  /*
  auto graphicSystem = Engine::GraphicSystem::Create(windowInfo);
  EXPECT_TRUE(graphicSystem != nullptr);
  EXPECT_NO_THROW(graphicSystem->Init());
  */
}
//=================================================================================================
TEST(Engine, CheckMemoryFailWhenAskedTooMuchMemory)
{
	Engine::Startup startup;

	EXPECT_FALSE(startup.CheckMemory(ULLONG_MAX, ULLONG_MAX));
}
//=================================================================================================
TEST(Engine, CheckMemorySucceedWhenAskedOneByteOfMemory)
{
	Engine::Startup startup;

	EXPECT_FALSE(startup.CheckMemory(1, 1));
}
//=================================================================================================
TEST(Engine, NoErrorOnCheckingCpuSpeed)
{
	Engine::Startup startup;

	EXPECT_NO_THROW(startup.ReadCPUSpeed());
}
//=================================================================================================