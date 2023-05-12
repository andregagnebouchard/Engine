#pragma once
/*
- You need to find a way to introduce behaviour more quickly, like 'pausable'. Probably through inheritance. Or another design

- Next step is to rework the queue, and make the component system more extendable

C++ Stuff
- Check how inline affect performance
- Learn templated polymorphism

Ideas
- Maybe create UI tools in Python, like animation slicer
- Maybe create a script for the huge boilerplate code of each entity

Improvements
- I think I don't need the double queue system
- Should refactor so that each system has one queue of event, and dispatch them to the components. This would be aligned in memory, and get rid of all the queues
- You need to get rid of all these shared pointers of events. Events should be on the stack
- You need to specify the logic between input and logic event. It is not clear if the input system should throw logic or input events
- Might want to get rid of the forward declarations






Event without heap
#include <array>
#include <cstdint>
#include <functional>

constexpr std::size_t kMaxEvents = 100; // Maximum number of events.
constexpr std::size_t kMaxListeners = 10; // Maximum number of listeners.

using EventId = std::uint32_t; // Event identifier.
using EventCallback = std::function<void()>; // Event callback.

struct Event {
  EventId id;
  EventCallback callback;
};

class EventSystem {
public:
  void RegisterListener(EventId eventId, const EventCallback& callback) {
    if (m_NumListeners >= kMaxListeners) {
      // Too many listeners, handle error.
      return;
    }
    m_Listeners[m_NumListeners++] = { eventId, callback };
  }

  void UnregisterListener(const EventCallback& callback) {
    for (std::size_t i = 0; i < m_NumListeners; ++i) {
      if (m_Listeners[i].callback == callback) {
        // Found listener, remove it by shifting the remaining elements.
        std::memmove(&m_Listeners[i], &m_Listeners[i + 1], (m_NumListeners - i - 1) * sizeof(Event));
        --m_NumListeners;
        break;
      }
    }
  }

  void PostEvent(EventId eventId) {
    if (m_NumEvents >= kMaxEvents) {
      // Too many events, handle error.
      return;
    }
    m_Events[m_NumEvents++] = { eventId, nullptr };
  }

  template<typename T>
  void PostEvent(EventId eventId, T&& payload) {
    if (m_NumEvents >= kMaxEvents) {
      // Too many events, handle error.
      return;
    }
    m_EventPayloads[m_NumEvents].emplace<T>(std::forward<T>(payload));
    m_Events[m_NumEvents++] = { eventId, [payload = &m_EventPayloads[m_NumEvents - 1]]() {
      const auto& p = payload->get<T>();
      HandleEvent<T>(p);
    }};
  }

  void ProcessEvents() {
    for (std::size_t i = 0; i < m_NumEvents; ++i) {
      const auto& event = m_Events[i];
      for (std::size_t j = 0; j < m_NumListeners; ++j) {
        const auto& listener = m_Listeners[j];
        if (listener.id == event.id && listener.callback) {
          listener.callback();
        }
      }
      m_Events[i].callback = nullptr;
    }
    m_NumEvents = 0;
    m_EventPayloads.fill({});
  }

private:
  template<typename T>
  void HandleEvent(const T& payload) {
    // Do something with the payload of the event.
  }

  std::array<Event, kMaxEvents> m_Events;
  std::size_t m_NumEvents = 0;
  std::array<std::variant<std::monostate, int, float, double>, kMaxEvents> m_EventPayloads; // Fixed-size pool for event payloads.
  std::array<Event, kMaxListeners> m_Listeners;
  std::size_t m_NumListeners = 0;
};
*/
