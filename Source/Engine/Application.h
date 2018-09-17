#pragma once
#include "Engine\IApplication.h"
#include <SFML\Window.hpp>
#include <memory>
using namespace std;

namespace Engine
{
	class Application : public IApplication
  {
  public:
    void Init(shared_ptr<IApplicationOption> options) override;
    void Shutdown() override;

    shared_ptr<ISystemInput> GetSystemInput() const override;
    shared_ptr<ISystemGraphic> GetSystemGraphic() const override;
    void RunLoop() override;
  private:
    shared_ptr<ISystemInput> m_SystemInput;
    shared_ptr<ISystemGraphic> m_SystemGraphic;
  };
}
