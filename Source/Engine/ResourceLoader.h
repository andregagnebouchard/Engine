#pragma once
#include "Resource.h"
namespace Engine
{
  class ResourceLoader
  {
  public:
    shared_ptr<void> Load(wstring filename, Resource::Type type);
    void Close(shared_ptr<void> data, Resource::Type type);
  };
}