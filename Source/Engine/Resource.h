#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <memory>
using namespace std;
namespace Engine
{
  namespace ResourceConstants
  {
    const int maxResourceNameLen = 128;
  }
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

    wstring GetFilePath() const { return m_FilePath; };
		wstring GetName() const { return m_Name; };
    unsigned int GetByteSize() const { return m_Size; };
    Type GetType() const { return m_Type; };

  private:
    wstring m_FilePath;
    unsigned int m_Size;
    Type m_Type;
		wstring m_Name;
  };


  class AudioResource : public Resource
  {
  public:
    AudioResource(const wstring& filepath, const wstring& name, sf::Sound* sound);
    ~AudioResource() = default;
    sf::Sound* GetSound() const { return m_Sound; };
  private:
    sf::Sound *m_Sound;
  };

  class GraphicResource : public Resource
  {
  public:
    GraphicResource(const wstring& filepath, const wstring& name, sf::Sprite* sprite);
    ~GraphicResource() = default;

    sf::Sprite* GetSprite() const { return m_Sprite; };
  private:
    sf::Sprite *m_Sprite;
  };
}