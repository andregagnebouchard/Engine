#pragma once
#include <Engine\ISystem.h>
#include <Engine\Typedef.h>
#include <memory>
#include <string>
using namespace std;
namespace Engine
{
	struct WindowInfo
	{
		uint Width;
		uint Length;
		string Title;
	};

	class IGraphicSystem : public ISystem
	{
	public:
    static shared_ptr<IGraphicSystem> Create(WindowInfo windowInfo);
		~IGraphicSystem() = default;

		// ISystem
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;

		// IGraphicSystem
		virtual void Resize(uint width, uint height) = 0;
	};
}