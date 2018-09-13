#pragma once
#include <memory>
#include <map>
#include "Resource.h"
namespace Engine
{
  class ResourceCache
  {
  public:
    void Init();
    shared_ptr<Resource> GetResource(int id);

    int GetSize();
    // This will invalidate all the resources previously returned
    void Clear();
  private:
    map<int, shared_ptr<Resource>> m_Ressources;
    int m_Size;
  };
}