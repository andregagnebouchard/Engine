#include "stdafx.h"
#include <Engine\EventDefinition.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\EntityIdCounter.h>
#include "Collision.h"
#include "CollisionEvent.h"
#include "LevelGenerator.h"
#include "EntityCreatedPayload.h"
using namespace Engine;
namespace Game
{
	LevelGeneratorLogicComponent::LevelGeneratorLogicComponent(int entityId) :
		m_EntityId(entityId)
	{
	};

	void LevelGeneratorLogicComponent::Update()
	{
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Pacman", EntityIdCounter::GenerateEntityId(), make_shared<PositionPayload>(Point{ 0.0f, 0.0f })));
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Pause", EntityIdCounter::GenerateEntityId(), nullptr));
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Debug", EntityIdCounter::GenerateEntityId(), nullptr));
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Collision", EntityIdCounter::GenerateEntityId(), nullptr));

		GenerateBigDots();
		GenerateGhost();
		DeleteItself();
	}

	void LevelGeneratorLogicComponent::DeleteItself() const
	{
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), Engine::EntityEvent::Type::Delete, L"LevelGenerator", m_EntityId, nullptr));
	}
	void LevelGeneratorLogicComponent::GenerateSmallDots() const
	{
		for (float row(1); row < 10; row++)
			for (float col(3); col < 10; col++)
				Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"SmallDot", EntityIdCounter::GenerateEntityId(), make_shared<PositionPayload>(Point{ col * 32, row * 32 })));
	}
	void LevelGeneratorLogicComponent::GenerateBigDots() const
	{
			Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"BigDot", EntityIdCounter::GenerateEntityId(), make_shared<PositionPayload>(Point{ 1*32, 32 })));
			Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"BigDot", EntityIdCounter::GenerateEntityId(), make_shared<PositionPayload>(Point{ 2*32, 32 })));
			Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"BigDot", EntityIdCounter::GenerateEntityId(), make_shared<PositionPayload>(Point{ 3*32, 32 })));
	}
	void LevelGeneratorLogicComponent::GenerateGhost() const
	{
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"BlueGhost", EntityIdCounter::GenerateEntityId(), make_shared<PositionPayload>(Point{ 5 * 32, 5 * 32 })));
	}
}