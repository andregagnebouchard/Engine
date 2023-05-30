#include "stdafx.h"
#include "Grid.h"
#include "GameEventIds.h"
#include <Engine\EventDefinition.h>
#include "MoveEvent.h"
#include "DebugState.h"
#include "CollisionEvent.h"
#include "EntityCreatedPayload.h"
#include <assert.h>
using namespace Engine;
namespace Game
{
	GridLogicComponent::GridLogicComponent(int entityId, Engine::Grid* grid) :
		m_EntityId(entityId),
		m_Grid(grid),
		m_EventCallback(bind(&GridLogicComponent::OnEvent, this, placeholders::_1))
	{
	}

	void GridLogicComponent::Init()
	{
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));

		// Subscribe to the move event of ANY entity in the game, to write them in the grid
		Messager::Attach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), Event::Key::AnyValue));
	}

	void GridLogicComponent::Shutdown()
	{
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));
		Messager::Detach(&m_EventCallback, Event::Key(static_cast<int>(EventDefinition::Id::GAME_LOGIC), static_cast<int>(GameEventId::Move), Event::Key::AnyValue));
	}

	void GridLogicComponent::OnEvent(const shared_ptr<Event> event)
	{
		const Event::Type eventType = event->GetType();
		if (eventType == Event::Type::Entity)
			HandleEntityEvent(dynamic_pointer_cast<EntityEvent>(event));
		else if (eventType == Event::Type::Logic) // Move
			HandleMoveEvent(dynamic_pointer_cast<LogicEvent>(event));
		else
			throw invalid_argument("Grid logic component received an unknown event type");
	}

	void GridLogicComponent::Update()
	{
		// Nothing, purely event based
	}

	void GridLogicComponent::HandleEntityEvent(const shared_ptr<EntityEvent> ev)
	{
		if (ev->GetActionType() == EntityEvent::Type::Create)
			HandleCreateEntityEvent(ev);
		else if (ev->GetActionType() == EntityEvent::Type::Delete)
			HandleDeleteEntityEvent(ev);
	}

	void GridLogicComponent::HandleMoveEvent(const shared_ptr<LogicEvent> event)
	{
		const auto ev = dynamic_pointer_cast<MoveEvent>(event->GetGameLogicEvent());
		const float newX = ev->GetDeltaX() + ev->GetInitialX();
		const float newY = ev->GetDeltaY() + ev->GetInitialY();

		const Engine::Grid::CellLocation initialLocation = m_Grid->GetCellLocationFromPosition(ev->GetInitialX(), ev->GetInitialY());
		const Engine::Grid::CellLocation newLocation = m_Grid->GetCellLocationFromPosition(newX, newY);
		if (!m_Grid->IsCellInbound(newLocation)) // Entity moved out of bound
			return;

		const int entityIdAtNewLocation = m_Grid->GetCellValue(newLocation);
		const int movingEntityId = event->GetEntityId();

		// No collision
		// Second condition is when the moving entity collide with itself, which can happen if the movement is within a single cell
		if (entityIdAtNewLocation == Engine::Grid::EmptyGridValue || entityIdAtNewLocation == movingEntityId)
		{
			m_Grid->SetCellValue(initialLocation, Engine::Grid::EmptyGridValue);
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

	void GridLogicComponent::HandleCreateEntityEvent(const shared_ptr<EntityEvent> ev)
	{
		if (ev->GetPayload() == nullptr || ev->GetPayload()->GetType() != static_cast<int>(EntityCreatedPayloadTypes::Position))
			return; // Not all entities are created at a position on the grid
		const Point point = dynamic_pointer_cast<PositionPayload>(ev->GetPayload())->GetPosition();
		const Engine::Grid::CellLocation location = m_Grid->GetCellLocationFromPosition(point.x, point.y);
		if (!m_Grid->IsCellInbound(location))
			assert(true); // Some entities, like pause, do not have a location on the grid. This used to be expected, but not anymore

		// There is already something in the grid at the position of the new entity
		// This might be normal in some scenarios, but any that I know right now, so throw
		if (m_Grid->GetCellValue(location) != Engine::Grid::EmptyGridValue)
			throw runtime_error("Creating an entity at the same location as another entity");

		m_Grid->SetCellValue(location, ev->GetEntityId());
		m_EntityToLocation.emplace(ev->GetEntityId(), location);
	}
	void GridLogicComponent::HandleDeleteEntityEvent(shared_ptr<EntityEvent> ev)
	{
		if(m_EntityToLocation.find(ev->GetEntityId()) == m_EntityToLocation.end())
			return; // Deleting an entity which doesn't have a location, which is normal
		m_Grid->SetCellValue(m_EntityToLocation.at(ev->GetEntityId()), Engine::Grid::EmptyGridValue);
	}
	//================================================Graphic==========================================================================================================
	GridGraphicComponent::GridGraphicComponent(int entityId, const Engine::Grid* grid, const DebugState* state) :
		m_EntityId(entityId),
		m_DebugState(state)
	{
	}

	void GridGraphicComponent::Update()
	{
		Event::Key k(static_cast<int>(EventDefinition::Id::RENDER_LINE));
		if (m_DebugState->isDebugModeActive)
			Messager::Fire(make_shared<RenderLineEvent>(
				k,
				Point{ 50, 50 },
				Point{ 250, 250 }));
	}
}