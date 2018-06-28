#pragma once
using namespace std;

namespace Engine
{
	class ISystem;
	class IApplication
	{
	public:
    virtual ~IApplication() = default;

    static shared_ptr<IApplication> Create();

		virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void AddSystem(shared_ptr<ISystem> system) = 0;

    virtual void RunLoop() = 0;
	};
}
