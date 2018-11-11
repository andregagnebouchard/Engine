#pragma once
#include <string>
namespace Engine
{
  class IComponent
  {
  public:
		enum class Type
		{
			Input,
			Graphic,
			Audio,
			Logic
		};
    virtual ~IComponent() = default;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Update(float dt) = 0;

		virtual wstring GetName() const = 0;
		virtual Type GetType() const = 0;
  };
}