#include <gtest\gtest.h>
#include <Engine\Resource.h>
#include <Engine\SystemGraphic.h>
#include <Engine\IApplicationOption.h>
using namespace Engine;
const wstring fileDir = L"..\\..\\Support\\Testing\\ApplicationTest\\";
//=================================================================================================
class ApplicationTest : public testing::Test
{
protected:

	virtual void SetUp()
	{
		m_Options = IApplicationOption::Create();
	}

	virtual void TearDown()
	{
	}
	shared_ptr<IApplicationOption> m_Options = nullptr;
};
//=================================================================================================
TEST_F(ApplicationTest, InitApplicationOptionWithValidFile)
{
	m_Options->Load(fileDir + L"ValidInit.xml");
}

TEST_F(ApplicationTest, InitApplicationOptionWithResourcelessFile)
{
	m_Options->Load(fileDir + L"ResourceLess.xml");
}

TEST_F(ApplicationTest, InitApplicationOptionWithEmptyFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"EmptyInit.xml"), invalid_argument);
}

TEST_F(ApplicationTest, InitApplicationOptionWithMissingFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L""), invalid_argument);
}

TEST_F(ApplicationTest, InitApplicationOptionWithMissingWindowHeightFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"MissingWindowHeight.xml"), invalid_argument);
}

TEST_F(ApplicationTest, InitApplicationOptionWithMissingWindowWidthFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"MissingWindowWidth.xml"), invalid_argument);
}