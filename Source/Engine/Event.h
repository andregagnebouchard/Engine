#pragma once
#include <Engine/IGameLogicEvent.h>
#include <Engine/IEntityCreatedPayload.h>
#include <Engine/MathStructs.h>
#include <string>
#include <memory>
using namespace std;
namespace Engine
{
  class Event
  {
  public:

    // Event key are unique identifiers for the event
    // We are using int as generic identifiers, to allow the Games to cast their own specific enums into int
    // The structure is very loose, but it generally follows this approach:
    // First is the engine event type (Audio, Graphic, Logic, etc)
    // Second is the game specific event type, such as "Entity died"for example
    // Third is the entity id, when the event is targeted towards a specific entity
    struct Key
    {
      Key();
      Key(int first);
      Key(int first, int second);
      Key(int first, int second, int third);

      static const int AnyValue = -12345; // Meaning we subscribe to all possible values for that key attribute

      int first = AnyValue;
      int second = AnyValue;
      int third = AnyValue;

      bool operator==(const Key& other) const
      {
        return (first == other.first
          && second == other.second
          && third == other.third);
      }
    };

    enum class Type
    {
      Input,
      Render,
			Entity,
      Logic,
      Audio,
      Unknown
    };

    Event(const Event::Key &key);
    Event();

    virtual Type GetType() const = 0;

    Event::Key GetKey() const { return m_Key; };
  private:
    const Event::Key m_Key;
  };

  class AudioEvent : public Event
  {
  public:
    AudioEvent(const Event::Key &key, const wstring& resourceName);
    wstring GetResourceName() const { return m_ResourceName; };
    Type GetType() const override { return Event::Type::Audio; };
  private:
    const wstring m_ResourceName;
  };

  class RenderSpriteEvent : public Event
  {
  public :
    RenderSpriteEvent(const Event::Key &key, const wstring &resourceName, float x, float y);
    wstring GetResourceName() const { return m_ResourceName; };
    float GetXPosition() const { return m_XPosition; };
    float GetYPosition() const { return m_YPosition; };
    Type GetType() const override { return Event::Type::Render; };
  private:
    const wstring m_ResourceName;
    const float m_XPosition;
    const float m_YPosition;
  };

  class RenderLineEvent : public Event
  {
  public:
    RenderLineEvent(const Event::Key &key, const Point &from, const Point &to);
    Point GetFrom() const { return m_From; };
    Point GetTo() const { return m_To; };
    Type GetType() const override { return Event::Type::Render; };
  private:
    const Point m_From;
    const Point m_To;
  };

  class InputEvent : public Event
  {
  public:
    enum class KeyState { Pressed, Released };
    InputEvent(const Event::Key &key, KeyState altKeyState, KeyState controlKeyState, KeyState shiftKeyState, KeyState systemKeyState);

    KeyState GetAltKeyState() const { return m_AltKeyState; };
    KeyState GetControlKeyState() const { return m_ControlKeyState; };
    KeyState GetShiftKeyState() const { return m_ShiftKeyState; };
    KeyState GetSystemKeyState() const { return m_SystemKeyState; };
    Type GetType() const override { return Event::Type::Input; };
  private:
    const KeyState m_AltKeyState;
    const KeyState m_ControlKeyState;
    const KeyState m_ShiftKeyState;
    const KeyState m_SystemKeyState;
  };

	class EntityEvent : public Event
	{
	public:
		enum class Type { Create, Delete };
		EntityEvent(const Event::Key &key, Type type, const wstring &name, int entityId, const shared_ptr<IEntityCreatedPayload> payload);

    int GetEntityId() const { return m_EntityId; }

		Type GetActionType() const { return m_Type; };
		wstring GetName() const { return m_Name; }; // This would be more efficient as an id, instead of a name
		Event::Type GetType() const override { return Event::Type::Entity; };
    shared_ptr<IEntityCreatedPayload> GetPayload() const { return m_Payload; }
	private:
		const wstring m_Name;
		const Type m_Type;
    const int m_EntityId;
    const Point m_Position;
    const shared_ptr<IEntityCreatedPayload> m_Payload;
	};

  class LogicEvent : public Event
  {
  public:
    LogicEvent(const Event::Key &key, const shared_ptr<IGameLogicEvent> gameLogicEvent);
    int GetEntityId() const { return m_EntityId; };
    int GetGameLogicEventId() const { return m_GameLogicEventId; };
    shared_ptr<IGameLogicEvent> GetGameLogicEvent() const { return m_GameLogicEvent; };
    Type GetType() const override { return Event::Type::Logic; };
  private:
    const int m_EntityId; // Could fill these in the constructor from the event key
    const int m_GameLogicEventId;
    const shared_ptr<IGameLogicEvent> m_GameLogicEvent;
  };
}

// Custom hashing function for Event::Key, in order to use them as keys in maps
namespace std
{
  template <>
  struct hash<Engine::Event::Key>
  {
    std::size_t operator()(const Engine::Event::Key& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return ((hash<int>()(k.first)
        ^ (hash<int>()(k.second) << 1)) >> 1)
        ^ (hash<int>()(k.third) << 1);
    }
  };
}