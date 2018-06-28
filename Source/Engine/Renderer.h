#pragma once
namespace Engine
{
  class Renderer
  {
  public:
    virtual ~Renderer();

    void Init();
    void Shutdown();
    void PreRender();
    void Render();
    void PostRender();
  };
}
