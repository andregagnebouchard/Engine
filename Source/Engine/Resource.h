#pragma once
#include <string>
#include <memory>
#include <Engine/Typedef.h>
using namespace std;
namespace Engine
{
  class ResourceLoader;
  class Resource
  {
  public:
    enum class Type
    {
      PNG,
			WAV
    };

		// The resource type will be deducted by the extension of the filepath
    Resource(const wstring &filepath, const wstring &name, shared_ptr<ResourceLoader> resourceLoader);

    wstring GetFilePath() const;
		wstring GetName() const;
    Byte GetSize() const;
    shared_ptr<void> GetData() const;
    Type GetType() const;

		void Load();
		bool IsLoaded() const;
  private:
    wstring m_FilePath;
		Byte m_Size;
    shared_ptr<void> m_Data;
    Type m_Type;
    bool m_IsLoaded;
		wstring m_Name;
    shared_ptr<ResourceLoader> m_ResourceLoader;
  };
}