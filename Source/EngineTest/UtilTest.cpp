#include <gtest\gtest.h>
#include <Engine\FileUtil.h>
#include <Engine\StringUtil.h>
using namespace Engine;
using namespace std;
// FileUtil
TEST(UtilTest, TestGetFileSizeStr)
{
	ASSERT_EQ(FileUtil::GetFileSize("..\\..\\Support\\Testing\\UtilTest\\23ByteFile.txt"), 23);
}

TEST(UtilTest, TestGetFileSizeWStr)
{
	ASSERT_EQ(FileUtil::GetFileSize(L"..\\..\\Support\\Testing\\UtilTest\\23ByteFile.txt"), 23);
}

TEST(UtilTest, TestGetFileSizeWStrWithoutFile)
{
	EXPECT_THROW(FileUtil::GetFileSize(L"INVALID_PATH"), invalid_argument);
}

TEST(UtilTest, TestGetFileSizeStrWithoutFile)
{
	EXPECT_THROW(FileUtil::GetFileSize("INVALID_PATH"), invalid_argument);
}

TEST(UtilTest, TestGetFileExtension)
{
	ASSERT_EQ(FileUtil::GetExtension(L"Test.txt"), L"txt");
}

TEST(UtilTest, TestGetFileExtensionUpperCase)
{
	ASSERT_EQ(FileUtil::GetExtension(L"Test.TXT"), L"txt");
}

TEST(UtilTest, TestGetFileExtensionWithoutExtension)
{
	EXPECT_THROW(FileUtil::GetExtension(L"Test"), invalid_argument);
}

TEST(UtilTest, TestGetFileExtensionEmptyString)
{
	EXPECT_THROW(FileUtil::GetExtension(L""), invalid_argument);
}

TEST(UtilTest, TestToWStr)
{
	ASSERT_EQ(StringUtil::ToWStr("Allo"), L"Allo");
}

// String util
TEST(UtilTest, TestToStr)
{
	ASSERT_EQ(StringUtil::ToStr(L"Allo"), "Allo");
}

TEST(UtilTest, TestToWStrEmptyStr)
{
	ASSERT_EQ(StringUtil::ToWStr(""), L"");
}

TEST(UtilTest, TestToStrEmptyStr)
{
	ASSERT_EQ(StringUtil::ToStr(L""), "");
}