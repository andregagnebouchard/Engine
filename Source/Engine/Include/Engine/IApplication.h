#pragma once
#include <Engine/ISystemGraphic.h>
#include <Engine/ISystemInput.h>
#include <Engine/ISystemLogic.h>
#include <Engine/ISystemAudio.h>
#include <Engine/IApplicationOption.h>
#include <Engine/IEntityFactory.h>
#include <memory>
using namespace std;

namespace Engine
{
	class IApplication
	{
	public:
    virtual ~IApplication() = default;

		// Entry point for all games
    static shared_ptr<IApplication> Create();

		// Options : Contains all the game settings
		// EntityFactory : User-implemented class used to create entities
		virtual void Init(const shared_ptr<IApplicationOption> options, const shared_ptr<IGameEntityFactory> entityFactory) = 0;
    virtual void Shutdown() = 0;
    virtual void RunLoop() = 0;
	};
}
