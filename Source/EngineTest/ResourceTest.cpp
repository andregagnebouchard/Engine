#include <gtest\gtest.h>
#include <Engine\ResourceCache.h>
#include <tinyxml\tinyxml2.h>
using namespace Engine;
using namespace std;
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
TEST_F(ResourceTest, ResourceCacheLoadXmlFile)
{
  tinyxml2::XMLDocument xml_doc;

  tinyxml2::XMLError eResult = xml_doc.LoadFile("..\\..\\Support\\Testing\\ResourceCacheTest\\Resource.xml");
  if (eResult != tinyxml2::XML_SUCCESS)
    FAIL();

  tinyxml2::XMLNode* resource = xml_doc.FirstChildElement("DATA");
  resource = resource->FirstChildElement("RESOURCE");
  resource = resource->FirstChildElement("GRAPHIC");
  int id = atoi(resource->FirstChildElement("ID")->GetText());
  string name = resource->FirstChildElement("NAME")->GetText();
  string path = resource->FirstChildElement("PATH")->GetText();
}