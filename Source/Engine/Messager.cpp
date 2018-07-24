#pragma once
#include "stdafx.h"
#include "Messager.h"
namespace Engine
{
  unordered_map<Event::Id, set<const std::function<void(Event)>*>> Messager::m_Callbacks;
  void Messager::Attach(const std::function<void(Event)> *callback, Event::Id eventId)
  {
    m_Callbacks[eventId].insert(callback);
  }

  void Messager::Detach(const std::function<void(Event)> *callback, Event::Id eventId)
  {
    m_Callbacks[eventId].erase(callback);
  }

  void Messager::Fire(const Event &event)
  {
    for (auto callback : m_Callbacks[event.GetId()])
      (*callback)(event);
  }

  //=============
  // MessageQueue
  //=============
  MessageQueue::MessageQueue()
  {
    m_Callback = bind(&MessageQueue::OnEvent, this, placeholders::_1);
  }

  queue<Event>& MessageQueue::GetEvents()
  {
    return m_Events;
  }

  function<void(Event)>* MessageQueue::GetCallback()
  {
    return &m_Callback;
  }
  void MessageQueue::OnEvent(Event event)
  {
    m_Events.push(event);
  }
}