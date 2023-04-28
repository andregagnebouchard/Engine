#pragma once
#include <Engine/ISystemGraphic.h>
#include <Engine/ISystemInput.h>
#include <Engine/ISystemLogic.h>
#include <Engine/ISystemAudio.h>
#include <Engine/IApplicationOption.h>
#include <Engine/IEntityFactory.h>
using namespace std;

namespace Engine
{
	class IApplication
	{
	public:
    virtual ~IApplication() = default;

    static shared_ptr<IApplication> Create();

		// Options : Contains all the game settings
		// EntityFactory : User-implemented class used to create entities
		virtual void Init(shared_ptr<IApplicationOption> options, shared_ptr<IEntityFactory> entityFactory) = 0;
    virtual void Shutdown() = 0;

    virtual shared_ptr<ISystemInput> GetSystemInput() const = 0;
    virtual shared_ptr<ISystemGraphic> GetSystemGraphic() const = 0;
		virtual shared_ptr<ISystemLogic> GetSystemLogic() const = 0;
		virtual shared_ptr<ISystemAudio> GetSystemAudio() const = 0;
    virtual void RunLoop() = 0;
	};
}
