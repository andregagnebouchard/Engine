#pragma once
#include <string>
#include <memory>
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
      MP3
    };

    Resource(int id, wstring filepath, int size, shared_ptr<void> data, shared_ptr<ResourceLoader> resourceLoader);

    wstring GetFilePath();
    size_t GetSize();
    shared_ptr<void> GetData();
    Type GetType();
    int GetId();
  private:

    // The resource cache is the only one handling the loaded state
    friend class ResourceCache;
    void Load();
    void Close();
    bool IsLoaded();

    wstring m_FilePath;
    size_t m_Size;
    shared_ptr<void> m_Data;
    Type m_Type;
    bool m_IsLoaded;
    int m_Id;
    shared_ptr<ResourceLoader> m_ResourceLoader;
  };
}