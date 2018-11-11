#include <gtest\gtest.h>
#include <Engine\Resource.h>
#include <Engine\SystemGraphic.h>
#include <Engine\IApplication.h>
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
		m_Application = IApplication::Create();
	}

	virtual void TearDown()
	{
	}
	shared_ptr<IApplicationOption> m_Options = nullptr;
	shared_ptr<IApplication> m_Application = nullptr;
};

class ComponentFactory : public IComponentFactory
{
public:
	shared_ptr<IComponent> Create(const wstring &name) override
	{
		return nullptr;
	}
};
//=================================================================================================
TEST_F(ApplicationTest, LoadApplicationOptionWithValidFile)
{
	m_Options->Load(fileDir + L"ValidInit.xml");
}

TEST_F(ApplicationTest, LoadApplicationOptionWithResourcelessFile)
{
	m_Options->Load(fileDir + L"ResourceLess.xml");
}

TEST_F(ApplicationTest, LoadApplicationOptionWithEmptyFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"EmptyInit.xml"), invalid_argument);
}

TEST_F(ApplicationTest, LoadApplicationOptionWithMissingFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L""), invalid_argument);
}

TEST_F(ApplicationTest, LoadApplicationOptionWithMissingWindowHeightFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"MissingWindowHeight.xml"), invalid_argument);
}

TEST_F(ApplicationTest, LoadApplicationOptionWithMissingEntityName)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"MissingEntityName.xml"), invalid_argument);
}

TEST_F(ApplicationTest, LoadApplicationOptionWithMissingWindowWidthFile)
{
	EXPECT_THROW(m_Options->Load(fileDir + L"MissingWindowWidth.xml"), invalid_argument);
}

TEST_F(ApplicationTest, CreateApplication)
{
	IApplication::Create();
}
TEST_F(ApplicationTest, InitApplicationWithAllParametersNullptr)
{
	EXPECT_THROW(m_Application->Init(nullptr, nullptr), invalid_argument);
}

TEST_F(ApplicationTest, InitApplicationWithParameterComponentFactoryNullptr)
{
	EXPECT_THROW(m_Application->Init(IApplicationOption::Create(), nullptr), invalid_argument);
}

TEST_F(ApplicationTest, InitApplicationWithParameterApplicationOptionNullptr)
{
	EXPECT_THROW(m_Application->Init(nullptr, make_shared<ComponentFactory>()), invalid_argument);
}

TEST_F(ApplicationTest, InitApplication)
{
	m_Options->Load(fileDir + L"ValidInit.xml");
	m_Application->Init(m_Options, make_shared<ComponentFactory>());
}