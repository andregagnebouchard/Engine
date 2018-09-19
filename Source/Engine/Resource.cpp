#include "stdafx.h"
#include "Resource.h"
#include "ResourceLoader.h"
#include "FileUtil.h"
#include "StringUtil.h"
namespace Engine
{
	Resource::Type FileExtensionToResourceType(std::wstring &ext)
	{
		if (ext == L"wav")
			return Resource::Type::Audio;
		else if (ext == L"png")
			return Resource::Type::Graphic;
		else
			throw runtime_error("Extension does not have a corresponding resource type:" + StringUtil::ToStr(ext));
	}

  Resource::Resource(const wstring &filepath, const wstring &name) :
    m_Data(nullptr),
    m_FilePath(filepath),
    m_Size(0),
    m_IsLoaded(false),
    m_Type(Resource::Type::Audio),
		m_Name(name)
  {
    if (m_Name.length() > RESOURCE_NAME_CHAR_MAX)
      throw invalid_argument("Resource name exceeds character limit of \"" + to_string(RESOURCE_NAME_CHAR_MAX) + "\" :\"" + StringUtil::ToStr(name));

		m_Size = FileUtil::GetFileSize(filepath);
		m_Type = FileExtensionToResourceType(FileUtil::GetExtension(filepath));
  }

  wstring Resource::GetFilePath() const
  {
    return m_FilePath;
  }
	Byte Resource::GetSize() const
  {
    return m_Size;
  }
  shared_ptr<void> Resource::GetData() const
  {
    return m_Data;
  }
  Resource::Type Resource::GetType() const
  {
    return m_Type;
  }
  bool Resource::IsLoaded() const
  {
    return m_IsLoaded;
  }
  void Resource::Load()
  {
    m_Data = ResourceLoader::Load(m_FilePath, m_Type);
    m_IsLoaded = true;
  }

	wstring Resource::GetName() const
	{
		return m_Name;
	}
}