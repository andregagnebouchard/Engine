#pragma once
#include "Engine\IApplication.h"
#include <memory>
using namespace std;

namespace Engine
{
  class ResourceCache;
	class EngineEntityFactory;
	class Application : public IApplication
  {
  public:
    Application() = default;
		~Application();
    void Init(const shared_ptr<IApplicationOption> options, const shared_ptr<IGameEntityFactory> entityFactory) override;
    void Shutdown() override;
    void RunLoop() override;
  private:
		shared_ptr<ISystemLogic> m_SystemLogic;
    shared_ptr<ISystemInput> m_SystemInput;
    shared_ptr<ISystemGraphic> m_SystemGraphic;
    shared_ptr<ISystemAudio> m_SystemAudio;
    shared_ptr<ResourceCache> m_ResourceCache;
		shared_ptr<EngineEntityFactory> m_EngineEntityFactory;

    const int nanoSecondPerFrame = 1000000000 / 60; // 60 fps
  };
}
