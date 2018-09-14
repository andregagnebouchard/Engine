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

  vector<const char*> arr;
  tinyxml2::XMLElement* resources = xml_doc.FirstChildElement("DATA")->FirstChildElement("RESOURCES");
  for (tinyxml2::XMLElement* resource = resources->FirstChildElement(); resource != NULL; resource = resource->NextSiblingElement())
  {
    const char* name;
    name = resource->Attribute("Name");
    arr.push_back(name);
    const char* id;
    id = resource->Attribute("ID");
    int idInt = atoi(id);
    arr.push_back(id);
  }
}