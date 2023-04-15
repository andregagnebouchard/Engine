#include "stdafx.h"
#include "ResourceCache.h"
#include "StringUtil.h"
#include "FileUtil.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
namespace Engine
{
	ResourceCache::ResourceCache(const unordered_map<wstring, wstring> &nameToFilepath) :
		m_NameToFilepath(nameToFilepath)
	{
	}

	Resource* ResourceCache::GetResource(const wstring& name)
	{
		if (m_NameToType.find(name) == m_NameToType.end()) // Unloaded
			LoadResource(name);
		
		switch (m_NameToType[name])
		{
		case Resource::Type::Graphic:
			return &m_NameToGraphicResource.find(name)->second;
		case Resource::Type::Audio:
			return &m_NameToAudioResource.find(name)->second;
		}
	}

	Resource::Type ResourceCache::FileExtensionToResourceType(const wstring& ext) const
	{
		if (ext == L"wav")
			return Resource::Type::Audio;
		else if (ext == L"png")
			return Resource::Type::Graphic;
		else
			throw runtime_error("Extension does not have a corresponding resource type:" + StringUtil::ToStr(ext));
	}

	void ResourceCache::LoadResource(const wstring& name)
	{
		wstring filepath = m_NameToFilepath[name];
		Resource::Type type = FileExtensionToResourceType(FileUtil::GetExtension(filepath));
		switch (type)
		{
		case Resource::Type::Audio:
			LoadAudioResource(filepath, name);
			break;
		case Resource::Type::Graphic:
			LoadGraphicResource(filepath, name);
			break;
		}
	}

	void ResourceCache::LoadGraphicResource(const wstring& filepath, const wstring& name)
	{
		m_NameToSfmlGraphicResource.insert(make_pair(name, SfmlGraphicResource()));
		SfmlGraphicResource &res = m_NameToSfmlGraphicResource[name];
		if (!res.texture.loadFromFile(StringUtil::ToStr(filepath)))
			throw runtime_error("Failed to load texture from file:" + StringUtil::ToStr(filepath));

		res.sprite.setTexture(res.texture);
		GraphicResource resource(filepath, name, &res.sprite);
		m_NameToGraphicResource.insert(make_pair(name, resource));
		m_NameToType.insert(make_pair(name, Resource::Type::Graphic));
	}
	void ResourceCache::LoadAudioResource(const wstring& filepath, const wstring& name)
	{
		m_NameToSfmlAudioResource.insert(make_pair(name, SfmlAudioResource()));
		SfmlAudioResource& res = m_NameToSfmlAudioResource[name];
		if (!res.buffer.loadFromFile(StringUtil::ToStr(filepath)))
			throw runtime_error("Failed to load audio from file:" + StringUtil::ToStr(filepath));
		res.sound.setBuffer(res.buffer);
		AudioResource resource(filepath, name, &res.sound);
		m_NameToAudioResource.insert(make_pair(name, resource));
		m_NameToType.insert(make_pair(name, Resource::Type::Audio));
	}
}