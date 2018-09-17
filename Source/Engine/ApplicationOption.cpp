#include "stdafx.h"
#include "ApplicationOption.h"
#include "StringUtil.h"
#include <tinyxml\tinyxml2.h>
#include "ResourceCache.h"
#include "ResourceLoader.h"
using namespace tinyxml2;
namespace Engine
{
	shared_ptr<IApplicationOption> IApplicationOption::Create()
	{
		return make_shared<ApplicationOption>();
	}

	void ApplicationOption::Init(const wstring &filename)
	{
		XMLDocument xml_doc;

		if (xml_doc.LoadFile(StringUtil::ToStr(filename).c_str()) != XML_SUCCESS)
			throw runtime_error("Error while loading XML file:" + StringUtil::ToStr(filename));

		XMLElement* data = xml_doc.FirstChildElement("DATA");
		XMLElement* resources = data->FirstChildElement("RESOURCES");
		XMLElement* window = data->FirstChildElement("WINDOW");

		// Window
		int width = atoi(window->Attribute("Width"));
		int height = atoi(window->Attribute("Height"));
		string name = window->Attribute("Name");
		bool isVisible = atoi(window->Attribute("IsVisibile")) == 0 ? false : true;

		// Resource
		auto resourceCache = make_shared<ResourceCache>();
		auto resourceLoader = make_shared<ResourceLoader>();
		for (auto resourceNode = resources->FirstChildElement(); resourceNode != NULL; resourceNode = resourceNode->NextSiblingElement())
		{
			string name = resourceNode->Attribute("Name");
			string path = resourceNode->Attribute("Path");
			resourceCache->AddResource(make_shared<Resource>(StringUtil::ToWStr(path), StringUtil::ToWStr(name), resourceLoader));
		}
	}


	ApplicationOption::ApplicationOption() :
		m_WindowWidth(640),
		m_WindowHeight(480),
		m_WindowName("Application"),
		m_IsWindowVisible(true)
	{
	}
		
	void ApplicationOption::SetWindowWidth(int width)
	{
		m_WindowWidth = width;
	}
	int ApplicationOption::GetWindowWidth() const
	{
		return m_WindowWidth;
	}
	void ApplicationOption::SetWindowHeight(int height)
	{
		m_WindowHeight = height;
	}
	int ApplicationOption::GetWindowHeight() const
	{
		return m_WindowHeight;
	}
	void ApplicationOption::SetWindowName(const string &name)
	{
		m_WindowName = name;
	}
	string ApplicationOption::GetWindowName() const
	{
		return m_WindowName;
	}
	void ApplicationOption::SetIsWindowVisible(bool isVisible)
	{
		m_IsWindowVisible = isVisible;
	}
	bool ApplicationOption::GetIsWindowVisible() const
	{
		return m_IsWindowVisible;
	}
}