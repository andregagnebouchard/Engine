#pragma once
#include <Engine/IEntityCreatedPayload.h>
#include <Engine/Event.h>
#include <Engine/MathStructs.h>
using namespace Engine;
namespace Game
{
	enum class EntityCreatedPayloadTypes
	{
		Position,
		DelayedEventCreated
	};

	class DelayedEventCreatedPayload : public IEntityCreatedPayload
	{
	public:
		DelayedEventCreatedPayload(Event::Key&& keyToEmit, int delayTickCount) : m_KeyToEmit(keyToEmit), m_DelayTickCount(delayTickCount) {}
		~DelayedEventCreatedPayload() = default;

		int GetType() const override { return static_cast<int>(EntityCreatedPayloadTypes::DelayedEventCreated); };
		Event::Key GetKeyToEmit() const { return m_KeyToEmit; };
		int GetDelayTickCount() const { return m_DelayTickCount; };
	private:
		Event::Key m_KeyToEmit;
		int m_DelayTickCount;
	};

	class PositionPayload : public IEntityCreatedPayload
	{
	public:
		PositionPayload(Point&& position) : m_Position(position) {};
		~PositionPayload() = default;

		int GetType() const override { return static_cast<int>(EntityCreatedPayloadTypes::Position); };
		Point GetPosition() const { return m_Position; };
	private:
		Point m_Position;
	};
}
