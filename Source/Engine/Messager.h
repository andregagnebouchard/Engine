#pragma once
#include <functional>
#include <queue>
#include <set>
#include "Event.h"
#include <unordered_map>
using namespace std;
//TODO: Use boost::hash_combine for custom hashing
namespace Engine
{
  class Messager
  {
  public:

    /*
    struct ActorEvent
    {
    Actor::Id actorId;
    Event::Id eventId;
    bool operator==(const EntityEvent &other) const { return actorId == other.actorId && eventId == other.eventId; }
    };
    */

    static void Attach(const std::function<void(Event)> *callback, Event::Id eventId);
    //void Attach(std::function<void(Event)> &callback, Event::Id eventId, ActorId actorId);

    static void Detach(const std::function<void(Event)> *callback, Event::Id eventId);
    //void Detach(std::function<void(Event)> &callback, Event::Id eventId, ActorId actorId);

    static void Fire(const Event &event);
  private:
    static unordered_map<Event::Id, set<const std::function<void(Event)>*>> m_Callbacks;
    //unordered_multimap<EntityEventKey, std::function<void(Event)>, decltype> m_EntityCallbacks;
  };

  class MessageQueue
  {
  public:
    MessageQueue();

    queue<Event>& GetQueue();
    function<void(Event)>* GetCallback();
		void Swap();
    
  private:
    void OnEvent(Event event);

    function<void(Event)> m_Callback;
    queue<Event> m_Queue1;
		queue<Event> m_Queue2;
		queue<Event> &m_CurrentQueue;
		int m_CurrentQueueId;

  };
}