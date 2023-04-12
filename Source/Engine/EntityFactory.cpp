#pragma once
#include "EntityFactory.h"
#include "Entity.h"
#include "StringUtil.h"
#include <Engine\IEntityFactory.h>
#include <Engine\IComponent.h>
#include <Engine\ISystemGraphic.h>
#include <Engine\ISystemInput.h>
#include <Engine\ISystemLogic.h>
#include "EventDefinition.h"
using namespace std;
namespace Engine
{
	EntityFactory::EntityFactory(shared_ptr<IEntityFactory> gameEntityFactory, shared_ptr<ISystemGraphic> systemGraphic, shared_ptr<ISystemLogic> systemLogic, shared_ptr<ISystemInput> systemInput) :
		m_GameEntityFactory(gameEntityFactory),
		m_SystemLogic(systemLogic),
		m_SystemGraphic(systemGraphic),
		m_SystemInput(systemInput),
		m_EntityIdCounter(0)
	{
		if (gameEntityFactory == nullptr) throw invalid_argument("The parameter \"gameEntityFactory\" is nullptr");
		if (systemGraphic == nullptr) throw invalid_argument("The parameter \"systemGraphic\" is nullptr");
		if (systemLogic == nullptr) throw invalid_argument("The parameter \"systemLogic\" is nullptr");
		if (systemInput == nullptr) throw invalid_argument("The parameter \"systemInput\" is nullptr");

		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));
	}

	shared_ptr<IEntity> EntityFactory::CreateEntity(const wstring& name)
	{
		// Create the entity using the entity factory provided by the user
		auto entity = m_GameEntityFactory->Create(name, m_EntityIdCounter++);
		if (entity == nullptr)
			throw runtime_error("The entity named \"" + StringUtil::ToStr(name) + "\" returned a nullptr from the EntityFactory provided by the game");

		// Register the component to its proper system
		for (auto& component : entity->GetComponents())
		{
			component->Init();
			switch (component->GetType())
			{
			case IComponent::Type::Audio:
				throw "Not implemented";
			case IComponent::Type::Graphic:
				m_SystemGraphic->Add(component);
				break;
			case IComponent::Type::Input:
				m_SystemInput->Add(component);
				break;
			case IComponent::Type::Logic:
				m_SystemLogic->Add(component);
				break;
			default:
				throw runtime_error("Unknown component type");
			}
		}
		m_Entities.emplace_back(entity);
		return m_Entities.back();
	}

	void EntityFactory::Update(float dt)
	{
		while (!m_MsgQueue.Empty())
		{
			shared_ptr<Event> &event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			if (event->GetType() != Event::Type::Entity)
				throw invalid_argument("Unknown event type handled by EntityFactory");

			auto ev = dynamic_pointer_cast<EntityEvent>(event);
			switch (ev->GetActionType())
			{
			case EntityEvent::Type::Create:
				CreateEntity(ev->GetName());
				break;
			case EntityEvent::Type::Delete:
				DeleteEntity(ev->GetName());
				break;
			}
		}
	}

	void EntityFactory::DeleteEntity(const wstring &name)
	{
		throw runtime_error("Not implemented");
	}
}
