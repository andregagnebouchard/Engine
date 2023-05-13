#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Resource.h"
#include <memory>
#include <unordered_map>
namespace Engine
{
  class ResourceCache
  {
  public:
    ResourceCache(const unordered_map<wstring, wstring> &nameToFilepath);

    // If the resource is not loaded, it will load it
    // Once a resource is loaded, it always is the same returned, and it stays in memory
    // until someone calls Clear()
    Resource* GetResource(const wstring &name);

    void Clear();
  private:
    struct SfmlGraphicResource
    {
      sf::Texture texture;;
      sf::Sprite sprite;
    };

    struct SfmlAudioResource
    {
      sf::SoundBuffer buffer;;
      sf::Sound sound;
    };

    void LoadResource(const wstring& name);
    void LoadGraphicResource(const wstring& filepath, const wstring& name);
    void LoadAudioResource(const wstring& filepath, const wstring& name);
    Resource::Type ResourceCache::FileExtensionToResourceType(const wstring& ext) const;

    // Would be way better to use the stack instead of the heap here
    unordered_map<wstring, Resource::Type> m_NameToType;
    unordered_map<wstring, GraphicResource> m_NameToGraphicResource;
    unordered_map<wstring, AudioResource> m_NameToAudioResource;
    unordered_map<wstring, wstring> m_NameToFilepath;
    unordered_map<wstring, SfmlGraphicResource> m_NameToSfmlGraphicResource;
    unordered_map<wstring, SfmlAudioResource> m_NameToSfmlAudioResource;
  };
}