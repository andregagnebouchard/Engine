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
    virtual void Update(float dt) = 0;

		virtual wstring GetName() const = 0;
		virtual Type GetType() const = 0;

		// The engine will handle the unique id attribution while creating the components in EntityFactory
		int GetId() const { return m_Id; }
		void SetId(int id) { m_Id = id; };
	private:
		int m_Id;
  };
}