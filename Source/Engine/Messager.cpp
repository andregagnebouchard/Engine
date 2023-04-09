#pragma once
#include "stdafx.h"
#include "Messager.h"
namespace Engine
{
  unordered_map<Event::Key, set<const std::function<void(shared_ptr<Event>)>*>> Messager::m_Callbacks;
  void Messager::Attach(const std::function<void(shared_ptr<Event>)> *callback, Event::Key eventKey)
  {
		if (callback == nullptr)
			throw invalid_argument("Argument \"callback\" is nullptr");

    m_Callbacks[eventKey].insert(callback);
  }

  void Messager::Detach(const std::function<void(shared_ptr<Event>)> *callback, Event::Key eventId)
  {
		if (callback == nullptr)
			throw invalid_argument("Argument \"callback\" is nullptr");

    m_Callbacks[eventId].erase(callback);
  }

  void Messager::Fire(const shared_ptr<Event> event)
  {
		//Logger::Log("Firing EventId " + itoa(event->GetKey().first) + "\t" + event->GetKey().second + "\t" + event->GetKey().third + "\t" + event->GetKey().fourth, Logger::Level::Info);
    for (auto callback : m_Callbacks[event->GetKey()])
      (*callback)(event);
  }

  //=============
  // MessageQueue
  //=============
  MessageQueue::MessageQueue() :
		m_CurrentQueue(m_Queue1),
		m_CurrentQueueId(1)
  {
    m_Callback = bind(&MessageQueue::OnEvent, this, placeholders::_1);
  }

  function<void(shared_ptr<Event>)>* MessageQueue::GetCallback()
  {
    return &m_Callback;
  }
  void MessageQueue::OnEvent(shared_ptr<Event> event)
  {
		m_CurrentQueue.push(event);
  }

	void MessageQueue::Swap()
	{
		if (m_CurrentQueueId == 1)
		{
			m_CurrentQueue = m_Queue2;
			m_CurrentQueueId = 2;
		}
		else
		{
			m_CurrentQueue = m_Queue1;
			m_CurrentQueueId = 1;
		}
	}

  void MessageQueue::Pop()
  {
    m_CurrentQueue.pop();
  }
  shared_ptr<Event> MessageQueue::Front()
  {
    return m_CurrentQueue.front();
  }
  bool MessageQueue::Empty()
  {
    return m_CurrentQueue.empty();
  }
}