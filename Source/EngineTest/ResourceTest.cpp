#include <gtest\gtest.h>
#include <Engine\Resource.h>
#include <Engine\ResourceCache.h>
#include <Engine\ResourceLoader.h>
#include <Engine\StringUtil.h>
#include <Engine\FileUtil.h>
#include <Engine\constant.h>
#include <tinyxml\tinyxml2.h>
using namespace Engine;
using namespace std;
const wstring PNG_RESOURCE_PATH = L"..\\..\\Support\\Testing\\ResourceCacheTest\\BLACK_SQUARE_10x9.png";
const wstring WAV_RESOURCE_PATH = L"..\\..\\Support\\Testing\\ResourceCacheTest\\WavFile.wav";
const wstring PNG_RESOURCE_NAME = L"PngResource";
const wstring WAV_RESOURCE_NAME = L"WavResource";
//=================================================================================================
class ResourceTest : public testing::Test
{
protected:

  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
    m_ResourceCache->Clear();
  }

  shared_ptr<ResourceCache> m_ResourceCache = make_shared<ResourceCache>();
};
//=================================================================================================
// Resource
TEST_F(ResourceTest, CreateWavResource)
{
	Resource resource(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	ASSERT_EQ(resource.GetType(), Resource::Type::PNG);
	ASSERT_EQ(resource.GetSize(), FileUtil::GetFileSize(PNG_RESOURCE_PATH));
	ASSERT_EQ(resource.GetName(), PNG_RESOURCE_NAME);
}

TEST_F(ResourceTest, CreatePngResource)
{
	Resource resource(WAV_RESOURCE_PATH, WAV_RESOURCE_NAME);
	ASSERT_EQ(resource.GetType(), Resource::Type::WAV);
	ASSERT_EQ(resource.GetSize(), FileUtil::GetFileSize(WAV_RESOURCE_PATH));
	ASSERT_EQ(resource.GetName(), WAV_RESOURCE_NAME);
}

TEST_F(ResourceTest, FailToCreateResourceWithInvalidFile)
{
	EXPECT_THROW(Resource resource(L"INVALID_PATH", PNG_RESOURCE_NAME), invalid_argument);
}

TEST_F(ResourceTest, CreateResourceWithNameExcidingCharacterLimit)
{
  const wstring filename = L"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234.png";
  EXPECT_EQ(filename.length(), RESOURCE_NAME_CHAR_MAX + 1);
  EXPECT_THROW(Resource resource(PNG_RESOURCE_PATH, filename), invalid_argument);
}

TEST_F(ResourceTest, LoadPngResource)
{
	Resource resource(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	ASSERT_EQ(resource.IsLoaded(), false);
	ASSERT_EQ(resource.GetData(), nullptr);
	resource.Load();
	ASSERT_EQ(resource.IsLoaded(), true);
	ASSERT_TRUE(resource.GetData() != nullptr);
}

TEST_F(ResourceTest, LoadWavResource)
{
	Resource resource(WAV_RESOURCE_PATH, WAV_RESOURCE_NAME);
	ASSERT_EQ(resource.IsLoaded(), false);
	ASSERT_EQ(resource.GetData(), nullptr);
	resource.Load();
	ASSERT_EQ(resource.IsLoaded(), true);
	ASSERT_TRUE(resource.GetData() != nullptr);
}

// ResourceCache
TEST_F(ResourceTest, CacheUnloadedResource)
{
	auto resource = make_shared<Resource>(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	m_ResourceCache->AddResource(resource);
	auto cachedResource = m_ResourceCache->GetResource(PNG_RESOURCE_NAME);
	ASSERT_EQ(resource, cachedResource);
	ASSERT_EQ(cachedResource->IsLoaded(), true);
	ASSERT_TRUE(cachedResource->GetData() != nullptr);
}

TEST_F(ResourceTest, CacheLoadedResource)
{
	auto resource = make_shared<Resource>(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	resource->Load();
	m_ResourceCache->AddResource(resource);
	resource = m_ResourceCache->GetResource(PNG_RESOURCE_NAME);
	ASSERT_EQ(resource->IsLoaded(), true);
	ASSERT_TRUE(resource->GetData() != nullptr);
}

TEST_F(ResourceTest, GetUncachedResource)
{
	EXPECT_THROW(m_ResourceCache->GetResource(PNG_RESOURCE_NAME), invalid_argument);
}

TEST_F(ResourceTest, FailToCacheTwoResourceWithSameName)
{
	auto resource1 = make_shared<Resource>(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	m_ResourceCache->AddResource(resource1);
	auto resource2 = make_shared<Resource>(WAV_RESOURCE_PATH, PNG_RESOURCE_NAME); // Different path
	EXPECT_THROW(m_ResourceCache->AddResource(resource2), invalid_argument);
}

TEST_F(ResourceTest, ClearEmptyCache)
{
	m_ResourceCache->Clear();
}

TEST_F(ResourceTest, ClearUnEmptyCache)
{
	auto resource = make_shared<Resource>(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	m_ResourceCache->AddResource(resource);
	m_ResourceCache->Clear();
}

TEST_F(ResourceTest, CacheTwoResourceWithSameNameWhileClearingCache)
{
	auto resource = make_shared<Resource>(PNG_RESOURCE_PATH, PNG_RESOURCE_NAME);
	m_ResourceCache->AddResource(resource);
	m_ResourceCache->Clear();
	m_ResourceCache->AddResource(resource);
}