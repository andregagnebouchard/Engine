#include "stdafx.h"
#include "SystemLogic.h"
#include "Messager.h"
namespace Engine
{
	SystemLogic::SystemLogic()
	{
	}

	void SystemLogic::Init()
	{
	}

	void SystemLogic::Shutdown()
	{
	}

	void SystemLogic::Update(float dt)
	{
	}

	void SystemLogic::Add(shared_ptr<IComponent> component)
	{
		//TODO: Map vs vector?
		// Map could validate its id is already registered
	}
}