#pragma once
#include <functional>
#include <queue>
#include <set>
#include <memory>
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

    static void Attach(const function<void(shared_ptr<Event>)> *callback, Event::Id eventId);
    //void Attach(std::function<void(Event)> &callback, Event::Id eventId, ActorId actorId);

    static void Detach(const function<void(shared_ptr<Event>)> *callback, Event::Id eventId);
    //void Detach(std::function<void(Event)> &callback, Event::Id eventId, ActorId actorId);

    static void Fire(const shared_ptr<Event> event);
  private:
    static unordered_map<Event::Id, set<const function<void(shared_ptr<Event>)>*>> m_Callbacks;
    //unordered_multimap<EntityEventKey, std::function<void(Event)>, decltype> m_EntityCallbacks;
  };

  class MessageQueue
  {
  public:
    MessageQueue();

    queue<shared_ptr<Event>>& GetQueue();
    function<void(shared_ptr<Event>)>* GetCallback();
		void Swap();
    
  private:
    void OnEvent(shared_ptr<Event> event);

    function<void(shared_ptr<Event>)> m_Callback;
    queue<shared_ptr<Event>> m_Queue1;
		queue<shared_ptr<Event>> m_Queue2;
		queue<shared_ptr<Event>> &m_CurrentQueue;
		int m_CurrentQueueId;

  };
}