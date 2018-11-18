#pragma once
#include "stdafx.h"
#include "Messager.h"
namespace Engine
{
  unordered_map<Event::Id, set<const std::function<void(shared_ptr<Event>)>*>> Messager::m_Callbacks;
  void Messager::Attach(const std::function<void(shared_ptr<Event>)> *callback, Event::Id eventId)
  {
		if (callback == nullptr)
			throw invalid_argument("Argument \"callback\" is nullptr");

    m_Callbacks[eventId].insert(callback);
  }

  void Messager::Detach(const std::function<void(shared_ptr<Event>)> *callback, Event::Id eventId)
  {
		if (callback == nullptr)
			throw invalid_argument("Argument \"callback\" is nullptr");

    m_Callbacks[eventId].erase(callback);
  }

  void Messager::Fire(const shared_ptr<Event> event)
  {
		Logger::Log("Firing EventId" + static_cast<int>(event->GetId()), Logger::Level::Info);
    for (auto callback : m_Callbacks[event->GetId()])
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

  queue<shared_ptr<Event>>& MessageQueue::GetQueue()
  {
    return m_CurrentQueue;
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
}