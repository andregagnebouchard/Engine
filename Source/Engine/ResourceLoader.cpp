#include "stdafx.h"
#include "ResourceLoader.h"
namespace Engine
{
  shared_ptr<void> ResourceLoader::Load(wstring filename, Resource::Type type)
  {
    switch (type)
    {
    case Resource::Type::PNG:
      break;
    case Resource::Type::MP3:
      break;
    }
    return nullptr;
  }
  void ResourceLoader::Close(shared_ptr<void> data, Resource::Type type)
  {
    switch (type)
    {
    case Resource::Type::PNG:
      break;
    case Resource::Type::MP3:
      break;
    }
  }
}