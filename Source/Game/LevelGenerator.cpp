#include "stdafx.h"
#include <Engine\EventDefinition.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\EntityIdCounter.h>
#include "Collision.h"
#include "CollisionEvent.h"
#include "LevelGenerator.h"
using namespace Engine;
namespace Game
{
	LevelGeneratorLogicComponent::LevelGeneratorLogicComponent(int entityId) :
		m_EntityId(entityId)
	{
	};

	void LevelGeneratorLogicComponent::Update(float dt)
	{
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Pacman", EntityIdCounter::GenerateEntityId(), Engine::Point{ 0, 0 }));
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Pause", EntityIdCounter::GenerateEntityId(), Engine::Point{ -1, -1 }));
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Debug", EntityIdCounter::GenerateEntityId(), Engine::Point{ -1, -1 }));
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"Collision", EntityIdCounter::GenerateEntityId(), Engine::Point{ -1, -1 }));

		// Delete itself, to not generate level twice
		Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::DELETE_ENTITY)), Engine::EntityEvent::Type::Delete, L"LevelGenerator", m_EntityId, Engine::Point{ -1, -1 }));

		for (float row(1); row < 10; row++)
			for (float col(3); col < 10; col++)
				Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"SmallDot", EntityIdCounter::GenerateEntityId(), Engine::Point{ col*32, row*32 }));
		for (float row(1); row < 10; row++)
			for (float col(1); col < 3; col++)
				Engine::Messager::Fire(make_shared<Engine::EntityEvent>(Engine::Event::Key(static_cast<int>(Engine::EventDefinition::Id::CREATE_ENTITY)), Engine::EntityEvent::Type::Create, L"BigDot", EntityIdCounter::GenerateEntityId(), Engine::Point{ col * 32, row*32}));
	}
}