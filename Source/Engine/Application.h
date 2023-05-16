#pragma once
#include "Engine\ApplicationOption.h"
#include <memory>
using namespace std;

namespace Engine
{
  class ResourceCache;
  class SystemAudio;
	class EngineEntityFactory;
  class IGameEntityFactory;
  class SystemLogic;
  class SystemInput;
  class SystemGraphic;
  class SystemAudio;
  class ResourceCache;
	class Application
  {
  public:
    Application() = default;
		~Application();
    void Init(const shared_ptr<ApplicationOption> options, const shared_ptr<IGameEntityFactory> entityFactory);
    void Shutdown();
    void RunLoop();
  private:
		shared_ptr<SystemLogic> m_SystemLogic;
    shared_ptr<SystemInput> m_SystemInput;
    shared_ptr<SystemGraphic> m_SystemGraphic;
    shared_ptr<SystemAudio> m_SystemAudio;
    shared_ptr<ResourceCache> m_ResourceCache;
		shared_ptr<EngineEntityFactory> m_EngineEntityFactory;

    const int nanoSecondPerFrame = 1000000000 / 60; // 60 fps
  };
}
