#pragma once
#include "Resource.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
using namespace std;
namespace Engine
{
  class ResourceLoader
  {
  public:
    shared_ptr<void> Load(const wstring &filename, Resource::Type type) const;
	private:
		shared_ptr<void> LoadPng(const wstring &filename) const;
		shared_ptr<void> LoadWav(const wstring &filename) const;
  };
}