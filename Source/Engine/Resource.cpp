#include "stdafx.h"
#include "Resource.h"
#include "FileUtil.h"
#include "StringUtil.h"
namespace Engine
{
	Resource::Type FileExtensionToResourceType(std::wstring &ext)
	{
		if (ext == L"wav")
			return Resource::Type::Audio;
		else if (ext == L"png")
			return Resource::Type::Graphic;
		else
			throw runtime_error("Extension does not have a corresponding resource type:" + StringUtil::ToStr(ext));
	}

  Resource::Resource(const wstring &filepath, const wstring &name, Type type) :
    m_FilePath(filepath),
    m_Size(0),
    m_Type(type)
  {
    if (m_Name.length() > RESOURCE_NAME_CHAR_MAX)
      throw invalid_argument("Resource name exceeds character limit of \"" + to_string(RESOURCE_NAME_CHAR_MAX) + "\" :\"" + StringUtil::ToStr(name));

		m_Size = FileUtil::GetFileSize(filepath);
		m_Type = FileExtensionToResourceType(FileUtil::GetExtension(filepath));
  }

  wstring Resource::GetFilePath() const
  {
    return m_FilePath;
  }
	Byte Resource::GetSize() const
  {
    return m_Size;
  }
  Resource::Type Resource::GetType() const
  {
    return m_Type;
  }

  AudioResource::AudioResource(const wstring& filepath, const wstring& name, sf::Sound* sound) :
    Resource(filepath, name, Resource::Type::Audio),
    m_Sound(sound)
  {
  }

  sf::Sound* AudioResource::GetSound() const
  {
    return m_Sound;
  }

	wstring Resource::GetName() const
	{
		return m_Name;
	}
  GraphicResource::GraphicResource(const wstring& filepath, const wstring& name, sf::Sprite* sprite) :
    Resource(filepath, name, Resource::Type::Graphic),
    m_Sprite(sprite)
  {
  }

  sf::Sprite* GraphicResource::GetSprite() const
  {
    return m_Sprite;
  }
}