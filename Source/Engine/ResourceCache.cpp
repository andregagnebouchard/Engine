#include "stdafx.h"
#include "ResourceCache.h"
#include "ResourceLoader.h"
#include "StringUtil.h"
namespace Engine
{
	void ResourceCache::AddResource(shared_ptr<Resource> resource)
	{
		if (m_Resources.find(resource->GetName()) != m_Resources.end())
			throw invalid_argument("Resource already cached:" + StringUtil::ToStr(resource->GetName()));

		m_Resources[resource->GetName()] = resource;
	}

  shared_ptr<Resource> ResourceCache::GetResource(const wstring &name) const
  {
		auto resourceIt = m_Resources.find(name);
		if(resourceIt == m_Resources.end())
			throw invalid_argument("Resource not cached:" + StringUtil::ToStr(name));

		auto resource = resourceIt->second;
    if (!resource->IsLoaded())
      resource->Load();

    return resource;
  }
  void ResourceCache::Clear()
  {
    m_Resources.clear();
  }
}