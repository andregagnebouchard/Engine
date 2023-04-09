#pragma once
#include <Engine/IEvent.h>
#include <functional>
#include <queue>
#include <set>
#include <memory>
using namespace std;

namespace Engine
{
	class IEvent;
	class IMessager
	{
	public:
		virtual ~IMessager() = default;

		static shared_ptr<IMessager> Create();

		virtual void Attach(const function<void(shared_ptr<IEvent>)>* callback, IEvent::Id eventId) = 0;
		virtual void Detach(const function<void(shared_ptr<IEvent>)>* callback, IEvent::Id eventId) = 0;
		virtual void Fire(const shared_ptr<IEvent> event) = 0;