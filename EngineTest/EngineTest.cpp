// EngineTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tinyxml\tinyxml2.h>
using namespace tinyxml2;
int main()
{
	tinyxml2::XMLDocument xml_doc;

	tinyxml2::XMLError eResult = xml_doc.LoadFile("test.xml");
	if (eResult != tinyxml2::XML_SUCCESS) return false;

	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("empleados");
	if (root == nullptr) return false;

	tinyxml2::XMLElement* element = root->FirstChildElement("cantidad");
	if (element == nullptr) return false;

	return true;
}

