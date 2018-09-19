#include "stdafx.h"
#include "ResourceLoader.h"
#include "StringUtil.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
namespace Engine
{
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
    sf::Texture texture;
		if (!texture.loadFromFile(StringUtil::ToStr(filename)))
			throw runtime_error("Failed to load texture from file:" + StringUtil::ToStr(filename));

    return make_shared<sf::Sprite>(texture);
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