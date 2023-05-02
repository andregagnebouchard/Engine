#include "stdafx.h"
#include "Grid.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
#include "MoveEvent.h"
#include "CollisionEvent.h"
using namespace Engine;
namespace Game
{
	GridLogicComponent::GridLogicComponent(int entityId, WorldGrid* grid) :
		m_EntityId(entityId),
		m_Grid(grid)
	{
	}

	void GridLogicComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));

		// Subscribe to the move event of ANY entity in the game
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), Event::Key::AnyValue));
	}
	void GridLogicComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty())
		{
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			Event::Type eventType = event->GetType();
			if (eventType == Event::Type::Entity)
				HandleEntityEvent(dynamic_pointer_cast<EntityEvent>(event));
			else if (eventType == Event::Type::Logic) // Move
				HandleMoveEvent(dynamic_pointer_cast<LogicEvent>(event));
			else
				throw invalid_argument("Grid logic component received an unknown event type");
		}
	}

	void GridLogicComponent::HandleEntityEvent(shared_ptr<EntityEvent> ev)
	{
		if (ev->GetActionType() == EntityEvent::Type::Create)
			HandleCreateEntityEvent(ev);
		else if (ev->GetActionType() == EntityEvent::Type::Delete)
			HandleDeleteEntityEvent(ev);
	}

	void GridLogicComponent::HandleMoveEvent(shared_ptr<LogicEvent> event)
	{
		auto ev = dynamic_pointer_cast<MoveEvent>(event->GetGameLogicEvent());
		float newX = ev->GetDeltaX() + ev->GetInitialX();
		float newY = ev->GetDeltaY() + ev->GetInitialY();

		CellLocation initialLocation = m_Grid->GetCellLocationFromPosition(ev->GetInitialX(), ev->GetInitialY());
		CellLocation newLocation = m_Grid->GetCellLocationFromPosition(newX, newY);
		if (!m_Grid->IsCellInbound(newLocation))
			return; // Some entities, like pause, do not have a location on the grid. This is expected, so don't throw

		int entityIdAtNewLocation = m_Grid->GetCellValue(newLocation);
		int movingEntityId = event->GetEntityId();

		// No collision
		// Second condition is when the moving entity collide with itself, which can happen if the movement is within a single cell
		if (entityIdAtNewLocation == WorldGrid::EmptyGridValue || entityIdAtNewLocation == movingEntityId)
		{
			m_Grid->SetCellValue(initialLocation, WorldGrid::EmptyGridValue);
			m_Grid->SetCellValue(newLocation, event->GetEntityId());
		}
		else
		{
			// There is a bug here. When two entities collide, what do we write?
			m_EntityToLocation.at(movingEntityId) = newLocation;
			Messager::Fire(make_shared<LogicEvent>(
				Event::Key
				(
					static_cast<int>(Engine::EventDefinition::Id::GAME_LOGIC),
					static_cast<int>(GameEventId::Collision)
				),
				make_shared<CollisionEvent>(movingEntityId, entityIdAtNewLocation)
				));
		}
	}

	void GridLogicComponent::HandleCreateEntityEvent(shared_ptr<EntityEvent> ev)
	{
		Point point = ev->GetPosition();
		CellLocation location = m_Grid->GetCellLocationFromPosition(point.x, point.y);
		if (!m_Grid->IsCellInbound(location))
			return; // Some entities, like pause, do not have a location on the grid. This is expected, so don't throw

		// There is already something in the grid at the position of the new entity
		// This might be normal in some scenarios, but any that I know right now, so throw
		if (m_Grid->GetCellValue(location) != WorldGrid::EmptyGridValue)
			throw runtime_error("Creating an entity at the same location as another entity");

		m_Grid->SetCellValue(location, ev->GetEntityId());
		m_EntityToLocation.emplace(ev->GetEntityId(), location);
	}
	void GridLogicComponent::HandleDeleteEntityEvent(shared_ptr<EntityEvent> ev)
	{
		if(m_EntityToLocation.find(ev->GetEntityId()) == m_EntityToLocation.end())
			return; // Deleting an entity without a location
		m_Grid->SetCellValue(m_EntityToLocation.at(ev->GetEntityId()), WorldGrid::EmptyGridValue);
	}
	//================================================Input==========================================================================================================
	GridInputComponent::GridInputComponent(int entityId) :
		m_EntityId(entityId)
	{
	};

	void GridInputComponent::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::KEY_O_PRESS)));
	}

	void GridInputComponent::Update(float dt)
	{
		while (!m_MsgQueue.Empty()) {
			shared_ptr<Event> event = m_MsgQueue.Front();
			m_MsgQueue.Pop();
			if (event->GetType() != Event::Type::Input)
				throw invalid_argument("A non-input event was caught by an input component");

			auto ev = dynamic_pointer_cast<InputEvent>(event);

			// There is only one key subscribed, no need to check which one was pressed

		}
	}
}