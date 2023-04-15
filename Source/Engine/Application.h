#pragma once
#include "Engine\IApplication.h"
#include <Engine\ISystemLogic.h>
#include <SFML\Window.hpp>
#include <memory>
using namespace std;

namespace Engine
{
  class ResourceCache;
	class EntityFactory;
	class Application : public IApplication
  {
  public:
		~Application();
    void Init(shared_ptr<IApplicationOption> options, shared_ptr<IEntityFactory> entityFactory) override;
    void Shutdown() override;

    shared_ptr<ISystemInput> GetSystemInput() const override;
    shared_ptr<ISystemGraphic> GetSystemGraphic() const override;
		shared_ptr<ISystemLogic> GetSystemLogic() const override;
    shared_ptr<ISystemAudio> GetSystemAudio() const override;

    void RunLoop() override;
  private:
		shared_ptr<ISystemLogic> m_SystemLogic;
    shared_ptr<ISystemInput> m_SystemInput;
    shared_ptr<ISystemGraphic> m_SystemGraphic;
    shared_ptr<ISystemAudio> m_SystemAudio;
    shared_ptr<ResourceCache> m_ResourceCache;
		shared_ptr<EntityFactory> m_EntityFactory;
  };
}
