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
			throw invalid_argument("Error while loading XML file:" + StringUtil::ToStr(filename));

		auto Throw = [&filename](const string &parameter) {throw invalid_argument("Did not find a value for the parameter \"" + parameter + "\" in the file \"" + StringUtil::ToStr(filename)); };

		// Window
		if (XMLElement* window = xml_doc.FirstChildElement("WINDOW"))
		{
			if (const char* width = window->Attribute("Width")) m_WindowWidth = atoi(width); else Throw("WINDOW::Width");
			if (const char* height = window->Attribute("Height")) m_WindowHeight = atoi(height); else Throw("WINDOW::Height");
			if (const char* name = window->Attribute("Name")) m_WindowName = name; else Throw("WINDOW::Name");
			if (const char* isVisible = window->Attribute("IsVisible")) m_IsWindowVisible = atoi(isVisible) != 0; else Throw("WINDOW::IsVisible");
		}
		else
			Throw("WINDOW");

		// Resource
		if (XMLElement* resources = xml_doc.FirstChildElement("RESOURCES"))
		{
			auto resourceCache = make_shared<ResourceCache>();
			auto resourceLoader = make_shared<ResourceLoader>();
			for (auto resourceNode = resources->FirstChildElement(); resourceNode != NULL; resourceNode = resourceNode->NextSiblingElement())
			{
				const char *name = resourceNode->Attribute("Name");
				const char *path = resourceNode->Attribute("Path");
				if (name == nullptr) Throw("RESSOURCES::Name");
				if (path == nullptr) Throw("RESSOURCES::Path");
				resourceCache->AddResource(make_shared<Resource>(StringUtil::ToWStr(path), StringUtil::ToWStr(name), resourceLoader));
			}
		}
		else
			// Technically not a mistake
			Logger::Log("Did not find any resource in the file \"" + StringUtil::ToStr(filename), Logger::Level::Warning);
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