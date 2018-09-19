#include <gtest\gtest.h>
#include <gmock\gmock.h>
int main(int argc, char **argv)
{
	::testing::InitGoogleMock(&argc, argv);
	//testing::GTEST_FLAG(filter) = "-GraphicSystemTest.*"; // Too long
	RUN_ALL_TESTS();
}