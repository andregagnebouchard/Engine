#pragma once
#include <Engine\ISystem.h>
#include <Engine\Typedef.h>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	class ISystemInput : public ISystem
	{
	public:
		//static shared_ptr<ISystemInput> Create();
		~ISystemInput() = default;
		
		// ISystem
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
	};
}