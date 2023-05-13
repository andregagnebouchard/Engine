#include "stdafx.h"
#include "ApplicationOption.h"
#include "StringUtil.h"
#include <tinyxml\tinyxml2.h>
#include "Resource.h"
#include "Entity.h"
using namespace tinyxml2;
namespace Engine
{
	shared_ptr<IApplicationOption> IApplicationOption::Create()
	{
		return make_shared<ApplicationOption>();
	}

	void ApplicationOption::Load(const wstring &filename)
	{
		XMLDocument xml_doc;
		if (xml_doc.LoadFile(StringUtil::ToStr(filename).c_str()) != XML_SUCCESS)
			throw invalid_argument("Error while loading XML file:" + StringUtil::ToStr(filename));


		// Window
		if (const XMLElement* window = xml_doc.FirstChildElement("WINDOW"))
		{
			if (const char* width = window->Attribute("Width")) 
				m_WindowWidth = atoi(width); 
			else 
				throw invalid_argument("Did not find a value for WINDOW::Width in the file \"" + StringUtil::ToStr(filename));

			if (const char* height = window->Attribute("Height")) 
				m_WindowHeight = atoi(height); 
			else 
				throw invalid_argument("Did not find a value for WINDOW::Height in the file \"" + StringUtil::ToStr(filename));

			if (const char* name = window->Attribute("Name")) 
				m_WindowName = name; 
			else 
				throw invalid_argument("Did not find a value for WINDOW::Name in the file \"" + StringUtil::ToStr(filename));
		}
		else
			throw invalid_argument("Did not find a value for WINDOW in the file \"" + StringUtil::ToStr(filename));

		// Resource
		if (const XMLElement* resources = xml_doc.FirstChildElement("RESOURCES"))
		{
			for (auto resourceNode = resources->FirstChildElement(); resourceNode != NULL; resourceNode = resourceNode->NextSiblingElement())
			{
				const char *name = resourceNode->Attribute("Name");
				const char *path = resourceNode->Attribute("Path");
				if (name == nullptr) 
					throw invalid_argument("Did not find a value for RESSOURCES::Name in the file \"" + StringUtil::ToStr(filename));
				if (path == nullptr) 
					throw invalid_argument("Did not find a value for RESSOURCES::Path in the file \"" + StringUtil::ToStr(filename));

				m_ResourceNameToFilepath.insert(make_pair(StringUtil::ToWStr(name), StringUtil::ToWStr(path)));
			}
		}
		else
			// Not having any ressource is "technically" not a mistake
			Logger::Log("Did not find any resource in the file \"" + StringUtil::ToStr(filename), Logger::Level::Warning);
	}

	ApplicationOption::ApplicationOption() :
		m_WindowWidth(640), // Default value if not provided by the file option
		m_WindowHeight(480),
		m_WindowName("Application"),
		m_IsWindowVisible(true)
	{
	}
}