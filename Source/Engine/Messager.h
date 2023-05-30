#pragma once
#include <functional>
#include <queue>
#include <unordered_set>
#include <memory>
#include "Event.h"
#include <unordered_map>
using namespace std;
namespace Engine
{
  class Messager
  {
  public:
    // Attach a callback to an event key, which will be called when an event with that key is fired
    static void Attach(const function<void(shared_ptr<Event>)> *callback, const Event::Key &eventKey);

    // Detach a callback from an event key
    static void Detach(const function<void(shared_ptr<Event>)> *callback, const Event::Key &eventKey);

    // Broadcast an event, which will synchronously call all callbacks subscribed to its key
    static void Fire(const shared_ptr<Event> event);
  private:
    static void ValidateEventKey(const Event::Key &key);
    static unordered_map<Event::Key, unordered_set<const function<void(shared_ptr<Event>)>*>> m_Callbacks;
  };
}