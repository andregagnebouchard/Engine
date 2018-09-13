#include "stdafx.h"
#include "ResourceCache.h"
#include "ResourceLoader.h"
namespace Engine
{
  void ResourceCache::Init()
  {
    // Load XML file
    auto resourceLoader = make_shared<ResourceLoader>();
    auto data = make_shared<string>("Allo mon gars!");
    auto ressource = make_shared<Resource>(0, L"AnyPath", 10, data, resourceLoader);
    m_Ressources[0] = ressource;
  }
  shared_ptr<Resource> ResourceCache::GetResource(int id)
  {
    auto ressource = m_Ressources[id];
    if (!ressource->IsLoaded())
      ressource->Load();

    return ressource;
  }
  void ResourceCache::Clear()
  {
    for (auto ressource : m_Ressources)
      ressource.second->Close();
    m_Ressources.clear();
  }
}