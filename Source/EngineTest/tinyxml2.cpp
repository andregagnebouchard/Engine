#include <gtest/gtest.h>
#include <tinyxml\tinyxml2.h>
TEST(tinyxml2_test, useTinyXml2)
{
	tinyxml2::XMLDocument xml_doc;

	tinyxml2::XMLError eResult = xml_doc.LoadFile("..\\..\\Support\\Testing\\TinyXmlLauncherTest.ini");
	if (eResult != tinyxml2::XML_SUCCESS) 
		FAIL();

  tinyxml2::XMLNode* launcher = xml_doc.FirstChildElement("DATA")->FirstChildElement("LAUNCHER");
  std::string processName = launcher->FirstChildElement("PROCESS_NAME")->GetText();
  size_t screenWidth = atoi(launcher->FirstChildElement("SCREEN_WIDTH")->GetText());
  size_t screenLength = atoi(launcher->FirstChildElement("SCREEN_LENGTH")->GetText());
}