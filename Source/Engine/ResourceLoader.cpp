#include "stdafx.h"
#include "ResourceLoader.h"
#include "StringUtil.h"
#include <SFML/Audio/SoundBuffer.hpp>
namespace Engine
{
  shared_ptr<void> ResourceLoader::Load(const wstring &filename, Resource::Type type)
  {
    switch (type)
    {
    case Resource::Type::PNG:
			return LoadPng(filename);
      break;
    case Resource::Type::WAV:
			return LoadWav(filename);
      break;
		default:
			throw invalid_argument("Unknown resource type to load");
    }
    return nullptr;
  }

	shared_ptr<void> ResourceLoader::LoadPng(const wstring &filename)
	{
		auto texture = make_shared<sf::Texture>();
		if (!texture->loadFromFile(StringUtil::ToStr(filename)))
			throw runtime_error("Failed to load texture from file:" + StringUtil::ToStr(filename));

		return texture;
	}

	shared_ptr<void> ResourceLoader::LoadWav(const wstring &filename)
	{
		sf::SoundBuffer buffer;
		if(!buffer.loadFromFile(StringUtil::ToStr(filename)))
			throw runtime_error("Failed to load audio from file:" + StringUtil::ToStr(filename));

		auto sound = make_shared<sf::Sound>();
		sound->setBuffer(buffer);
		return sound;
	}
}