#pragma once
#include <string>
using namespace std;
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

		virtual void Init() = 0; // Called when the entity is created
    virtual void Shutdown() = 0;
    virtual void Update() = 0;

		virtual Type GetType() const = 0; // Can we remove this?

		// The engine will handle the unique id attribution while creating the components in EntityFactory
		virtual int GetId() const = 0;
  };
}