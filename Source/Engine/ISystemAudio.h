#pragma once
#include <Engine\ISystem.h>
#include <Engine\Typedef.h>
#include <memory>
using namespace std;
namespace Engine
{
	class ISystemAudio : public ISystem
	{
	public:
		~ISystemAudio() = default;

		// ISystem
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;
		virtual void Add(const shared_ptr<IComponent> component) = 0;
		virtual void Remove(const shared_ptr<IComponent> component) = 0;
	};
}