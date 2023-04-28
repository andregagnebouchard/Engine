#pragma once
#include "constant.h"
#include <Engine/IGameLogicEvent.h>
using namespace std;
namespace Engine
{
  class Event
  {
  public:
    struct Key
    {
      Key();
      Key(int first);
      Key(int first, int second);
      Key(int first, int second, int third);
      Key(int first, int second, int third, int fourth);

      int first = 0;
      int second = 0;
      int third = 0;
      int fourth = 0;

      bool operator==(const Key& other) const
      {
        return (first == other.first
          && second == other.second
          && third == other.third
          && fourth== other.fourth);
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

    Event::Key GetKey() const;
  private:
    const Event::Key m_Key;
  };

  class AudioEvent : public Event
  {
  public:
    AudioEvent(Event::Key key, const wstring& resourceName);
    wstring GetResourceName() const;
    Type GetType() const override;
  private:
    wstring m_ResourceName;
  };

  class RenderEvent : public Event
  {
  public :
    RenderEvent(Event::Key key, const wstring &resourceName, const float x, const float y);
    wstring GetResourceName() const;
    float GetXPosition() const;
    float GetYPosition() const;
    Type GetType() const override;
  private:
    wstring m_ResourceName;
    float m_XPosition;
    float m_YPosition;
  };

  class InputEvent : public Event
  {
  public:
    enum class KeyState { Pressed, Released };
    InputEvent(Event::Key key, KeyState altKeyState, KeyState controlKeyState, KeyState shiftKeyState, KeyState systemKeyState);

    KeyState GetAltKeyState() const;
    KeyState GetControlKeyState() const;
    KeyState GetShiftKeyState() const;
    KeyState GetSystemKeyState() const;
    Type GetType() const override;
  private:
    KeyState m_AltKeyState;
    KeyState m_ControlKeyState;
    KeyState m_ShiftKeyState;
    KeyState m_SystemKeyState;
  };

	class EntityEvent : public Event
	{
	public:
		enum class Type { Create, Delete };
		EntityEvent(Event::Key key, Type type, const wstring &name);

		Type GetActionType() const;
		wstring GetName() const; // This should be an id, not a name
		Event::Type GetType() const override;
	private:
		wstring m_Name;
		Type m_Type;
	};

  class LogicEvent : public Event
  {
  public:
    LogicEvent(Event::Key key, shared_ptr<IGameLogicEvent> gameLogicEvent);
    int GetEntityId() const;
    int GetGameLogicEventId() const;
    shared_ptr<IGameLogicEvent> GetGameLogicEvent() const;
    Type GetType() const override;
  private:
    int m_EntityId; // Could fill these in the constructor from the event key
    int m_GameLogicEventId;
    shared_ptr<IGameLogicEvent> m_GameLogicEvent;
  };
}
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
        ^ (hash<int>()(k.third) << 1)
        ^ (hash<int>()(k.fourth) << 1);
    }
  };
}