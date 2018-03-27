#include <gtest/gtest.h>
#include <tinyxml\tinyxml2.h>
TEST(tinyxml2_test, useTinyXml2)
{
	tinyxml2::XMLDocument xml_doc;

	tinyxml2::XMLError eResult = xml_doc.LoadFile("..\\..\\Support\\Testing\\TinyXmlTest.xml");
	if (eResult != tinyxml2::XML_SUCCESS) 
		FAIL();

	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("empleados");
	if (root == nullptr) 
		FAIL();

	tinyxml2::XMLElement* element = root->FirstChildElement("cantidad");
	if (element == nullptr) 
		FAIL();
}