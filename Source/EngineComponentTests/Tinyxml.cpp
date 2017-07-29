#include "stdafx.h"
#include "CppUnitTest.h"
#include <tinyxml\tinyxml2.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineComponentTests
{		
	TEST_CLASS(TestTinyXml)
	{
	public:
		
		TEST_METHOD(UseTinyXml)
		{
			tinyxml2::XMLDocument xml_doc;

			tinyxml2::XMLError eResult = xml_doc.LoadFile("..\\..\\..\\Support\\Testing\\TinyXmlTest.xml");
			if (eResult != tinyxml2::XML_SUCCESS) Assert::Fail(L"Fail");

			tinyxml2::XMLNode* root = xml_doc.FirstChildElement("empleados");
			if (root == nullptr) Assert::Fail(L"Fail");

			tinyxml2::XMLElement* element = root->FirstChildElement("cantidad");
			if (element == nullptr) Assert::Fail(L"Fail");
		}
	};
}