#pragma once
using namespace std;

namespace Engine
{
	class ISystemInput;
  class ISystemGraphic;

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
