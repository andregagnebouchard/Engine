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

		auto Throw = [&filename](const string &parameter) {throw invalid_argument("Did not find a value for the parameter \"" + parameter + "\" in the file \"" + StringUtil::ToStr(filename)); };

		// Window
		if (XMLElement* window = xml_doc.FirstChildElement("WINDOW"))
		{
			if (const char* width = window->Attribute("Width")) m_WindowWidth = atoi(width); else Throw("WINDOW::Width");
			if (const char* height = window->Attribute("Height")) m_WindowHeight = atoi(height); else Throw("WINDOW::Height");
			if (const char* name = window->Attribute("Name")) m_WindowName = name; else Throw("WINDOW::Name");
		}
		else
			Throw("WINDOW");

		// Resource
		if (XMLElement* resources = xml_doc.FirstChildElement("RESOURCES"))
		{
			for (auto resourceNode = resources->FirstChildElement(); resourceNode != NULL; resourceNode = resourceNode->NextSiblingElement())
			{
				const char *name = resourceNode->Attribute("Name");
				const char *path = resourceNode->Attribute("Path");
				if (name == nullptr) Throw("RESSOURCES::Name");
				if (path == nullptr) Throw("RESSOURCES::Path");
        m_Resources.push_back(make_shared<Resource>(StringUtil::ToWStr(path), StringUtil::ToWStr(name)));
			}
		}
		else
			// Not having any ressource is "technically" not a mistake
			Logger::Log("Did not find any resource in the file \"" + StringUtil::ToStr(filename), Logger::Level::Warning);

		// Entity
		if (XMLElement* entities = xml_doc.FirstChildElement("ENTITIES"))
		{
			for (auto entityNode = entities->FirstChildElement(); entityNode != NULL; entityNode = entityNode->NextSiblingElement())
			{
				const char *name = entityNode->Attribute("Name");
				const char *logicComponent = entityNode->Attribute("LogicComponent");
				const char *graphicComponent = entityNode->Attribute("GraphicComponent");
				const char *inputComponent = entityNode->Attribute("InputComponent");

				if (name == nullptr) Throw("ENTITIES::Name");

				vector<wstring> components = { StringUtil::ToWStr(logicComponent), StringUtil::ToWStr(graphicComponent), StringUtil::ToWStr(inputComponent) };
				if(components.empty())
					Logger::Log("The entity \"" + StringUtil::ToStr(name) + "\" declared in the file \"" + StringUtil::ToStr(filename) + "\" do not have any component", Logger::Level::Warning);

				m_Entities.push_back(make_shared<EntityDeclaration>());
				m_Entities.back()->componentNames = components;
				m_Entities.back()->name = StringUtil::ToWStr(name);
			}
		}
		else
			// Not having any entity is "technically" not a mistake
			Logger::Log("Did not find any entity in the file \"" + StringUtil::ToStr(filename), Logger::Level::Warning);
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

  vector<shared_ptr<Resource>> ApplicationOption::GetResources() const
  {
    return m_Resources;
  }

	vector<shared_ptr<IApplicationOption::EntityDeclaration>> ApplicationOption::GetEntities() const
	{
		return m_Entities;
	}

	void ApplicationOption::AddResource(shared_ptr<Resource> resource)
	{
		m_Resources.push_back(resource);
	}
	void ApplicationOption::AddEntity(shared_ptr<EntityDeclaration> entity)
	{
		m_Entities.push_back(entity);
	}
}