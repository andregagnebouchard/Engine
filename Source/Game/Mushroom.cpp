#include "stdafx.h"
#include "Mushroom.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
using namespace Engine;
namespace Game
{
	//================================================Graphic==========================================================================================================
	MushroomGraphicComponent::MushroomGraphicComponent(int entityId, shared_ptr<MushroomState> state) : 
		m_EntityId(entityId), 
		m_State(state) 
	{
	};
	void MushroomGraphicComponent::Update(float dt)
	{
		Messager::Fire(make_shared<RenderEvent>(
			Event::Key(static_cast<int>(EventDefinition::Id::RENDER_SPRITE)),
			PickSpriteName(),
			m_State->posX,
			m_State->posY));
	}

	wstring MushroomGraphicComponent::PickSpriteName() const
	{
		if (m_State->actionState == MushroomActionState::MOVING)
		{
			if (m_State->direction == MushroomMovingDirection::DOWN)
			{
				if(m_State->movingFrame == 0)
					return L"MushroomMoving";
				if (m_State->movingFrame == 1)
					return L"MushroomMoving";
				if (m_State->movingFrame == 2)
					return L"MushroomMoving";
			}
			if (m_State->direction == MushroomMovingDirection::UP)
			{
				if (m_State->movingFrame == 0)
					return L"MushroomMoving";
				if (m_State->movingFrame == 1)
					return L"MushroomMoving";
				if (m_State->movingFrame == 2)
					return L"MushroomMoving";
			}
			if (m_State->direction == MushroomMovingDirection::LEFT)
			{
				if (m_State->movingFrame == 0)
					return L"MushroomMoving";
				if (m_State->movingFrame == 1)
					return L"MushroomMoving";
				if (m_State->movingFrame == 2)
					return L"MushroomMoving";
			}
			if (m_State->direction == MushroomMovingDirection::RIGHT)
			{
				if (m_State->movingFrame == 0)
					return L"MushroomMoving";
				if (m_State->movingFrame == 1)
					return L"MushroomMoving";
				if (m_State->movingFrame == 2)
					return L"MushroomMoving";
			}
		}
		return L"MushroomSprite";
	}

	//================================================Input==========================================================================================================
	MushroomInputComponent::MushroomInputComponent(int entityId) : 
		m_EntityId(entityId) 
	{
	};

	void MushroomInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_DOWN_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_UP_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_LEFT_PRESS)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_RIGHT_PRESS)));
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
				case static_cast<int>(Engine::EventDefinition::Id::KEY_DOWN_PRESS) :
					Messager::Fire(CreateMoveEvent(MushroomMovingDirection::DOWN));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_UP_PRESS) :
					Messager::Fire(CreateMoveEvent(MushroomMovingDirection::UP));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_LEFT_PRESS) :
					Messager::Fire(CreateMoveEvent(MushroomMovingDirection::LEFT));
					break;
				case static_cast<int>(Engine::EventDefinition::Id::KEY_RIGHT_PRESS) :
					Messager::Fire(CreateMoveEvent(MushroomMovingDirection::RIGHT));
					break;
			}
		}
	}

	shared_ptr<LogicEvent> MushroomInputComponent::CreateMoveEvent(MushroomMovingDirection direction)
	{
		int deltaX = 0;
		int deltaY = 0;
		switch (direction)
		{
		case MushroomMovingDirection::DOWN:
			deltaY = 10;
			break;
		case MushroomMovingDirection::UP:
			deltaY = -10;
			break;
		case MushroomMovingDirection::LEFT:
			deltaX = -10;
			break;
		case MushroomMovingDirection::RIGHT:
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
			make_shared<MoveMushroomLogicEvent>(deltaX, deltaY, direction)
			);
	}
	//================================================Logic==========================================================================================================
	MushroomLogicComponent::MushroomLogicComponent(int entityId, shared_ptr<MushroomState> state) : 
		m_EntityId(entityId), 
		m_State(state) 
	{
	};

	MoveMushroomLogicEvent::MoveMushroomLogicEvent(int deltaX, int deltaY, MushroomMovingDirection direction) : 
		m_DeltaX(deltaX),
		m_DeltaY(deltaY),
		m_Direction(direction)
	{
	};

	void MushroomLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::MushroomMove), m_EntityId));
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
		if (m_State->actionState != MushroomActionState::MOVING)
		{
			m_State->actionState = MushroomActionState::MOVING;
			m_State->movingFrame = 0;
		}

		if (ev->GetDirection() != m_State->direction)
		{
			m_State->direction = ev->GetDirection();
			m_State->movingFrame = 0;
		}

		m_State->posX += ev->GetDeltaX();
		m_State->posY += ev->GetDeltaY();
	}
	//================================================Audio==========================================================================================================
	MushroomAudioComponent::MushroomAudioComponent(int entityId) : 
		m_EntityId(entityId) 
	{
	};
	void MushroomAudioComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::MushroomMove), m_EntityId));
	}

	void MushroomAudioComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			auto ev = dynamic_pointer_cast<LogicEvent>(event);
			switch (static_cast<GameEventId>(ev->GetGameLogicEventId()))
			{
			case GameEventId::MushroomMove:
				Messager::Fire(CreateAudioEvent());
				break;
			}
		}
	}

	shared_ptr<AudioEvent> MushroomAudioComponent::CreateAudioEvent() const
	{
		Event::Key key(static_cast<int>(Engine::EventDefinition::Id::AUDIO));
		return make_shared<AudioEvent>(key, L"MushroomMoveSound");
	}
}