#include "stdafx.h"
#include "Event.h"
namespace Engine
{
  Event::Key::Key() : first(-1), second(-1), third(-1), fourth(-1){}
  Event::Key::Key(int first) : first(first), second(-1), third(-1), fourth(-1) {}
  Event::Key::Key(int first, int second) : first(first), second(second), third(-1), fourth(-1) {}
  Event::Key::Key(int first, int second, int third) : first(first), second(second), third(third), fourth(-1) {}
  Event::Key::Key(int first, int second, int third, int fourth) : first(first), second(second), third(third), fourth(fourth) {}

  Event::Event(Event::Key key) : 
    m_Key(key) 
  {
  }

  Event::Event() : 
    m_Key()
  {
  }
  InputEvent::InputEvent(Event::Key key, KeyState altKeyState, KeyState controlKeyState, KeyState shiftKeyState, KeyState systemKeyState) :
    Event(key),
    m_AltKeyState(altKeyState),
    m_ControlKeyState(controlKeyState),
    m_ShiftKeyState(shiftKeyState),
    m_SystemKeyState(systemKeyState)
  {
  }

  RenderEvent::RenderEvent(Event::Key key, const wstring& resourceName, const float x, const float y) :
    Event(key), 
    m_ResourceName(resourceName),
    m_XPosition(x),
    m_YPosition(y)
  {
  }

  InputEvent::KeyState InputEvent::GetAltKeyState() const
  {
    return m_AltKeyState;
  }
  InputEvent::KeyState InputEvent::GetControlKeyState() const
  {
    return m_ControlKeyState;
  }
  InputEvent::KeyState InputEvent::GetShiftKeyState() const
  {
    return m_ShiftKeyState;
  }
  InputEvent::KeyState InputEvent::GetSystemKeyState() const
  {
    return m_SystemKeyState;
  }

  wstring RenderEvent::GetResourceName() const 
  { 
    return m_ResourceName; 
  }

  float RenderEvent::GetXPosition() const
  {
    return m_XPosition;
  }
  float RenderEvent::GetYPosition() const
  {
    return m_YPosition;
  }

  Event::Key Event::GetKey() const
  { 
    return m_Key;
  }

  void Event::SetKey(Event::Key key)
  { 
    m_Key= key; 
  }

  Event::Type Event::GetType() const
  {
    return Event::Type::Unknown;
  }
  Event::Type RenderEvent::GetType() const
  { 
    return Event::Type::Render; 
  }

  Event::Type InputEvent::GetType() const
  {
    return Event::Type::Input;
  }

	EntityEvent::EntityEvent(Event::Key key, EntityEvent::Type type, const wstring &name) :
		Event(key),
		m_Type(type),
		m_Name(name)
	{
	}

	EntityEvent::Type EntityEvent::GetActionType() const
	{
		return m_Type;
	}
	wstring EntityEvent::GetName() const
	{
		return m_Name;
	}

	Event::Type EntityEvent::GetType() const
	{
		return Event::Type::Entity;
	}

  LogicEvent::LogicEvent(Event::Key key, shared_ptr<IGameLogicEvent> gameLogicEvent) : 
    Event(key),
    m_GameLogicEventId(key.second), 
    m_EntityId(key.third),
    m_GameLogicEvent(gameLogicEvent)
  {
  }

  Event::Type LogicEvent::GetType() const
  {
    return Event::Type::Logic;
  }

  int LogicEvent::GetEntityId() const
  {
    return m_EntityId;
  }

  int LogicEvent::GetGameLogicEventId() const
  {
    return m_GameLogicEventId;
  }

  shared_ptr<IGameLogicEvent> LogicEvent::GetGameLogicEvent() const
  {
    return m_GameLogicEvent;
  }

  AudioEvent::AudioEvent(Event::Key key, const wstring& resourceName) :
    Event(key),
    m_ResourceName(resourceName)
  {

  }
  wstring AudioEvent::GetResourceName() const
  {
    return m_ResourceName;
  }
  Event::Type AudioEvent::GetType() const
  {
    return Event::Type::Audio;
  }
}