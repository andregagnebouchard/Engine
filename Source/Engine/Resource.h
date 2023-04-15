#pragma once
#include <string>
#include <memory>
#include <Engine/Typedef.h>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;
namespace Engine
{
  class Resource
  {
  public:
    enum class Type
    {
      Graphic,
			Audio
    };

		// The resource type will be deducted by the extension of the filepath
    Resource(const wstring &filepath, const wstring &name, Type type);
    virtual ~Resource() = default;

    wstring GetFilePath() const;
		wstring GetName() const;
    Byte GetSize() const;
    Type GetType() const;

  private:
    wstring m_FilePath;
		Byte m_Size;
    Type m_Type;
		wstring m_Name;
  };


  class AudioResource : public Resource
  {
  public:
    AudioResource(const wstring& filepath, const wstring& name, sf::Sound* sound);
    ~AudioResource() = default;
    sf::Sound* GetSound() const;
  private:
    sf::Sound *m_Sound;
  };

  class GraphicResource : public Resource
  {
  public:
    GraphicResource(const wstring& filepath, const wstring& name, sf::Sprite* sprite);
    ~GraphicResource() = default;

    sf::Sprite* GetSprite() const;;
  private:
    sf::Sprite *m_Sprite;
  };
}