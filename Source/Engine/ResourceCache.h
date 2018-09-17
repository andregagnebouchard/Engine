#pragma once
#include <memory>
#include <map>
#include "Resource.h"
namespace Engine
{
  class ResourceCache
  {
  public:
		// Throw if a resource with the same name already exist
		void AddResource(shared_ptr<Resource> resource);

		// Guarentee that the returned resource is loaded
    shared_ptr<Resource> GetResource(const wstring &name) const;

    // This will invalidate all the resources previously returned
    void Clear();
  private:
    map<wstring, shared_ptr<Resource>> m_Resources;
    int m_Size;
  };
}