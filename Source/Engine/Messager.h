#pragma once
#include <functional>
#include <queue>
#include <set>
#include <memory>
#include "Event.h"
#include <unordered_map>
using namespace std;
namespace Engine
{
  class Messager
  {
  public:
    static void Attach(const function<void(shared_ptr<Event>)> *callback, Event::Key eventKey);
    static void Detach(const function<void(shared_ptr<Event>)> *callback, Event::Key eventKey);

    static void Fire(const shared_ptr<Event> event);
  private:
    static void ValidateEventKey(const Event::Key& key);
    static unordered_map<Event::Key, set<const function<void(shared_ptr<Event>)>*>> m_Callbacks;
  };

  class MessageQueue
  {
  public:
    MessageQueue();
    void Pop();
    shared_ptr<Event> Front();
    void Swap();
    bool Empty();
    function<void(shared_ptr<Event>)>* GetCallback();
    
  private:
    void OnEvent(shared_ptr<Event> event);

    function<void(shared_ptr<Event>)> m_Callback;
    queue<shared_ptr<Event>> m_Queue1;
		queue<shared_ptr<Event>> m_Queue2;
		queue<shared_ptr<Event>> &m_CurrentQueue;
		int m_CurrentQueueId;
  };
}