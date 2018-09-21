#pragma once
#include "Resource.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
#include <map>
#include <string>
using namespace std;
namespace Engine
{
  class ResourceLoader
  {
  public:
    static shared_ptr<void> Load(const wstring &filename, Resource::Type type);
	private:
    static shared_ptr<void> LoadGraphicResource(const wstring &filename);
    static shared_ptr<void> LoadAudioResource(const wstring &filename);
    static map<wstring, sf::Texture> m_TextureCache;
  };
}