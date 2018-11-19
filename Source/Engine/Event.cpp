#include "stdafx.h"
#include "Event.h"
namespace Engine
{
  Event::Event(Id id) : 
    m_Id(id) 
  {
  }

  Event::Event() : 
    m_Id(Id::UNKNOWN) 
  {
  }
  InputEvent::InputEvent(Id id, KeyState altKeyState, KeyState controlKeyState, KeyState shiftKeyState, KeyState systemKeyState) :
    Event(id),
    m_AltKeyState(altKeyState),
    m_ControlKeyState(controlKeyState),
    m_ShiftKeyState(shiftKeyState),
    m_SystemKeyState(systemKeyState)
  {
  }

  RenderEvent::RenderEvent(Id id, const wstring &resourceName) : 
    Event(id), 
    m_ResourceName(resourceName) 
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

  Event::Id Event::GetId() const
  { 
    return m_Id; 
  }

  void Event::SetId(Id id) 
  { 
    m_Id = id; 
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

	EntityEvent::EntityEvent(Id id, EntityEvent::Type type, const wstring &name) :
		Event(id),
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
}