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
			return Resource::Type::WAV;
		else if (ext == L"png")
			return Resource::Type::PNG;
		else
			throw runtime_error("Extension does not have a corresponding resource type:" + StringUtil::ToStr(ext));
	}

  Resource::Resource(const wstring &filepath, const wstring &name, shared_ptr<ResourceLoader> resourceLoader) :
    m_Data(nullptr),
    m_FilePath(filepath),
    m_Size(0),
    m_IsLoaded(false),
    m_Type(Resource::Type::WAV),
    m_ResourceLoader(resourceLoader),
		m_Name(name)
  {
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
    m_Data = m_ResourceLoader->Load(m_FilePath, m_Type);
    m_IsLoaded = true;
  }

	wstring Resource::GetName() const
	{
		return m_Name;
	}
}