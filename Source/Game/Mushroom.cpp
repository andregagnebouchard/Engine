#include "stdafx.h"
#include "Mushroom.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	shared_ptr<MushroomState> m_State;
	MushroomGraphicComponent::MushroomGraphicComponent(int entityId, shared_ptr<MushroomState> state) : m_EntityId(entityId), m_State(state) {};
	MushroomInputComponent::MushroomInputComponent(int entityId) : m_EntityId(entityId) {};
	MushroomLogicComponent::MushroomLogicComponent(int entityId, shared_ptr<MushroomState> state) : m_EntityId(entityId), m_State(state) {};
	MoveMushroomLogicEvent::MoveMushroomLogicEvent(int deltaX, int deltaY) : deltaX(deltaX), deltaY(deltaY) {};
	void MushroomGraphicComponent::Update(float dt)
	{
		Messager::Fire(make_shared<RenderEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)), 
			L"Mushroom",
			m_State->posX,
			m_State->posY));
	}

	void MushroomInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_DOWN_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_UP_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_LEFT_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_RIGHT_PRESS)));
	}

	void MushroomLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::MushroomMove), m_EntityId));
	}

	void MushroomInputComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Input)
				throw invalid_argument("A non-input event was caught by an input component");

			auto ev = dynamic_pointer_cast<InputEvent>(event);
			Engine::Event::Key key = ev->GetKey();
			
			switch (key.first)
			{
				case static_cast<int>(Engine::EventDefinition::Id::KEY_DOWN_PRESS):
					Messager::Fire(CreateMoveEvent(MoveMushroomLogicEvent::Direction::DOWN));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_UP_PRESS) :
					Messager::Fire(CreateMoveEvent(MoveMushroomLogicEvent::Direction::UP));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_LEFT_PRESS) :
					Messager::Fire(CreateMoveEvent(MoveMushroomLogicEvent::Direction::LEFT));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_RIGHT_PRESS) :
					Messager::Fire(CreateMoveEvent(MoveMushroomLogicEvent::Direction::RIGHT));
					break;
			}
		}
	}

	shared_ptr<LogicEvent> MushroomInputComponent::CreateMoveEvent(MoveMushroomLogicEvent::Direction direction)
	{
		int deltaX = 0;
		int deltaY = 0;
		switch (direction)
		{
			case MoveMushroomLogicEvent::Direction::DOWN:
				deltaY = 10;
				break;
			case MoveMushroomLogicEvent::Direction::UP:
				deltaY = -10;
				break;
			case MoveMushroomLogicEvent::Direction::LEFT:
				deltaX = -10;
				break;
			case MoveMushroomLogicEvent::Direction::RIGHT:
				deltaX = 10;
				break;
		}
		return make_shared<LogicEvent>(
				Event::Key
				(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::MushroomMove),
					m_EntityId
				),
			make_shared<MoveMushroomLogicEvent>(deltaX, deltaY)
			);
	}

	void MushroomLogicComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::MushroomMove:
				Move(dynamic_pointer_cast<MoveMushroomLogicEvent>(ev->GetGameLogicEvent()));
				break;
			}
		}
	}

	void MushroomLogicComponent::Move(shared_ptr<MoveMushroomLogicEvent> ev)
	{
		m_State->posX += ev->GetDeltaX();
		m_State->posY += ev->GetDeltaY();
	}
}