#include "stdafx.h"
#include "ResourceLoader.h"
#include "StringUtil.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
namespace Engine
{
  map<wstring, sf::Texture> ResourceLoader::m_TextureCache;

  shared_ptr<void> ResourceLoader::Load(const wstring &filename, Resource::Type type)
  {
    switch (type)
    {
    case Resource::Type::Graphic:
			return LoadGraphicResource(filename);
      break;
    case Resource::Type::Audio:
			return LoadAudioResource(filename);
      break;
		default:
			throw invalid_argument("Unknown resource type to load");
    }
    return nullptr;
  }

	shared_ptr<void> ResourceLoader::LoadGraphicResource(const wstring &filename)
	{
    if (m_TextureCache.find(filename) == m_TextureCache.end())
    {
      m_TextureCache[filename] = sf::Texture();
      if(!m_TextureCache[filename].loadFromFile(StringUtil::ToStr(filename)))
        throw runtime_error("Failed to load texture from file:" + StringUtil::ToStr(filename));
    }
    
    // Sprite needs their texture to be alive to work
    // We therefore need to store instances of textures somewhere to keep them alive
    return make_shared<sf::Sprite>(m_TextureCache[filename]);
	}

	shared_ptr<void> ResourceLoader::LoadAudioResource(const wstring &filename)
	{
		sf::SoundBuffer buffer;
		if(!buffer.loadFromFile(StringUtil::ToStr(filename)))
			throw runtime_error("Failed to load audio from file:" + StringUtil::ToStr(filename));

		auto sound = make_shared<sf::Sound>();
		sound->setBuffer(buffer);
		return sound;
	}
}