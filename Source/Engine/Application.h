#pragma once
#include "Engine\ApplicationOption.h"
#include <memory>
using namespace std;

namespace Engine
{
  class ApplicationImpl;
  class IGameEntityFactory;
  class ApplicationOption;
  class Window;
	class Application
  {
  public:
    Application();
    ~Application();
    void Init(const ApplicationOption &options, const shared_ptr<IGameEntityFactory> entityFactory);
    void Shutdown();
    void RunLoop();

    void Resize(unsigned int width, unsigned int height);
    void SetVisible(bool isVisible);
  private:
    // Somehow couldn't compile the game when using a unique_ptr
    // We use the implementation pointer pattern as the implementation details of the 
    // application includes multiple external dependencies, 
    // which we don't want to include in the games using this engine
    ApplicationImpl *m_Impl;
  };
}