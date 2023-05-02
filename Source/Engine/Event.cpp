#include "stdafx.h"
#include "Event.h"
namespace Engine
{
  Event::Key::Key() : first(AnyValue), second(AnyValue), third(AnyValue){}
  Event::Key::Key(int first) : first(first), second(AnyValue), third(AnyValue) {}
  Event::Key::Key(int first, int second) : first(first), second(second), third(AnyValue) {}
  Event::Key::Key(int first, int second, int third) : first(first), second(second), third(third) {}

  Event::Event(const Event::Key &key) : 
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

  RenderSpriteEvent::RenderSpriteEvent(Event::Key key, const wstring& resourceName, const float x, const float y) :
    Event(key), 
    m_ResourceName(resourceName),
    m_XPosition(x),
    m_YPosition(y)
  {
  }

  RenderLineEvent::RenderLineEvent(const Event::Key& key, const Point& from, const Point& to) :
    m_From(from),
    m_To(to)
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

  wstring RenderSpriteEvent::GetResourceName() const 
  { 
    return m_ResourceName; 
  }

  float RenderSpriteEvent::GetXPosition() const
  {
    return m_XPosition;
  }
  float RenderSpriteEvent::GetYPosition() const
  {
    return m_YPosition;
  }

  Event::Key Event::GetKey() const
  { 
    return m_Key;
  }

  Event::Type Event::GetType() const
  {
    return Event::Type::Unknown;
  }
  Event::Type RenderSpriteEvent::GetType() const
  { 
    return Event::Type::Render; 
  }

  Event::Type InputEvent::GetType() const
  {
    return Event::Type::Input;
  }

	EntityEvent::EntityEvent(Event::Key key, EntityEvent::Type type, const wstring &name, int entityId, const Point &&position) :
		Event(key),
		m_Type(type),
		m_Name(name),
    m_EntityId(entityId),
    m_Position(position)
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