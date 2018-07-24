#pragma once
#include "Event.h"
#include <memory>
using namespace std;
namespace Engine
{
	class Messager
	{
	public:
		static void Propagate(const Event &event);
		static void Subscribe(std::function<void(Event)> &callback);
		static void Unsubscribe(std::function<void(Event)> &callback);
	private:

	};
}