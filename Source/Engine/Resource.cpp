#include "stdafx.h"
#include "Resource.h"
#include "ResourceLoader.h"
namespace Engine
{
  Resource::Resource(int id, wstring filepath, int size, shared_ptr<void> data, shared_ptr<ResourceLoader> resourceLoader) :
    m_Data(data),
    m_FilePath(filepath),
    m_Size(size),
    m_IsLoaded(false),
    m_Type(Resource::Type::MP3),
    m_Id(id),
    m_ResourceLoader(resourceLoader)
  {
  }

  wstring Resource::GetFilePath()
  {
    return m_FilePath;
  }
  size_t Resource::GetSize()
  {
    return m_Size;
  }
  int Resource::GetId()
  {
    return m_Id;
  }
  shared_ptr<void> Resource::GetData()
  {
    return m_Data;
  }
  Resource::Type Resource::GetType()
  {
    return m_Type;
  }
  bool Resource::IsLoaded()
  {
    return m_IsLoaded;
  }
  void Resource::Close()
  {
    m_ResourceLoader->Close(m_Data, m_Type);
    m_IsLoaded = false;
  }
  void Resource::Load()
  {
    m_ResourceLoader->Load(m_FilePath, m_Type);
    m_IsLoaded = true;
  }
}