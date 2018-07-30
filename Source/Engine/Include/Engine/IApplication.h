#pragma once
#include <Engine/ISystemGraphic.h>
#include <Engine/ISystemInput.h>
using namespace std;

namespace Engine
{
	class IApplication
	{
	public:
    virtual ~IApplication() = default;

    static shared_ptr<IApplication> Create();

		virtual void Init() = 0;
    virtual void Shutdown() = 0;

    virtual shared_ptr<ISystemInput> GetSystemInput() const = 0;
    virtual shared_ptr<ISystemGraphic> GetSystemGraphic() const = 0;
    virtual void RunLoop() = 0;
	};
}
