#pragma once
#include "stdafx.h"
#include "Messager.h"
#include <array>
namespace Engine
{
  unordered_map<Event::Key, unordered_set<const std::function<void(shared_ptr<Event>)>*>> Messager::m_Callbacks;
  void Messager::Attach(const std::function<void(shared_ptr<Event>)> *callback, const Event::Key &eventKey)
  {
		if (callback == nullptr)
			throw invalid_argument("Argument \"callback\" is nullptr");
    ValidateEventKey(eventKey);

    m_Callbacks[eventKey].insert(callback);
  }

  void Messager::Detach(const std::function<void(shared_ptr<Event>)> *callback, const Event::Key &eventId)
  {
		if (callback == nullptr)
			throw invalid_argument("Argument \"callback\" is nullptr");

    m_Callbacks[eventId].erase(callback);
  }

  void Messager::Fire(const shared_ptr<Event> event)
  {
    // Check all key combinations with a wild card, and call their callbacks
    Event::Key& k = event->GetKey();
    ValidateEventKey(k);
    for (auto callback : m_Callbacks[k])
      (*callback)(event);

    if (k.third != Event::Key::AnyValue)
    {
      k.third = Event::Key::AnyValue;
      for (auto callback : m_Callbacks[k])
        (*callback)(event);
    }
    if (k.second != Event::Key::AnyValue)
    {
      k.second = Event::Key::AnyValue;
      for (auto callback : m_Callbacks[k])
        (*callback)(event);
    }
  }

  // Validate that not all attributes are wild cards, and that you don't have a non-wildcard attribute post a wildcard one
  void Messager::ValidateEventKey(const Event::Key& key)
  {
    if (key.first == Event::Key::AnyValue || (key.third != Event::Key::AnyValue && key.second == Event::Key::AnyValue))
      throw invalid_argument("Event key is not properly formated");
  }
}