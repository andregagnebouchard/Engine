#pragma once
#include "Engine\IApplication.h"
#include <SFML\Window.hpp>
#include <memory>
using namespace std;

namespace Engine
{
  class ISystem;

  class Application : public IApplication
  {
  public:
    void Init() override;
    void Shutdown() override;
    void AddSystem(shared_ptr<ISystem> system) override;

    void RunLoop() override;
  private:
    vector<shared_ptr<ISystem>> m_Systems;
  };
}
