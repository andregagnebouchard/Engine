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

  InputEvent::InputEvent(const Event::Key &key, KeyState altKeyState, KeyState controlKeyState, KeyState shiftKeyState, KeyState systemKeyState) :
    Event(key),
    m_AltKeyState(altKeyState),
    m_ControlKeyState(controlKeyState),
    m_ShiftKeyState(shiftKeyState),
    m_SystemKeyState(systemKeyState)
  {
  }

  RenderSpriteEvent::RenderSpriteEvent(const Event::Key &key, const wstring& resourceName, const float x, const float y) :
    Event(key), 
    m_ResourceName(resourceName),
    m_XPosition(x),
    m_YPosition(y)
  {
  }

  RenderLineEvent::RenderLineEvent(const Event::Key& key, const Point& from, const Point& to) :
    Event(key),
    m_From(from),
    m_To(to)
  {

  }

	EntityEvent::EntityEvent(const Event::Key &key, EntityEvent::Type type, const wstring &name, int entityId, const shared_ptr<IEntityCreatedPayload> payload) :
		Event(key),
		m_Type(type),
		m_Name(name),
    m_EntityId(entityId),
    m_Payload(payload)
	{
	}

  LogicEvent::LogicEvent(const Event::Key &key, const shared_ptr<IGameLogicEvent> gameLogicEvent) : 
    Event(key),
    m_GameLogicEventId(key.second), 
    m_EntityId(key.third),
    m_GameLogicEvent(gameLogicEvent)
  {
  }

  AudioEvent::AudioEvent(const Event::Key &key, const wstring& resourceName) :
    Event(key),
    m_ResourceName(resourceName)
  {
  }
}