#pragma once
#include "EntityFactory.h"
#include "Entity.h"
#include "StringUtil.h"
#include <Engine\IEntityFactory.h>
#include <Engine\IComponent.h>
#include <Engine\ISystemGraphic.h>
#include <Engine\ISystemInput.h>
#include <Engine\ISystemLogic.h>
#include <Engine\ISystemAudio.h>
#include "EventDefinition.h"
using namespace std;
namespace Engine
{
	EntityFactory::EntityFactory(shared_ptr<IEntityFactory> gameEntityFactory, shared_ptr<ISystemGraphic> systemGraphic, shared_ptr<ISystemLogic> systemLogic, shared_ptr<ISystemInput> systemInput, shared_ptr<ISystemAudio> systemAudio) :
		m_GameEntityFactory(gameEntityFactory),
		m_SystemLogic(systemLogic),
		m_SystemGraphic(systemGraphic),
		m_SystemInput(systemInput),
		m_SystemAudio(systemAudio)
	{
		if (gameEntityFactory == nullptr) throw invalid_argument("The parameter \"gameEntityFactory\" is nullptr");
		if (systemGraphic == nullptr) throw invalid_argument("The parameter \"systemGraphic\" is nullptr");
		if (systemLogic == nullptr) throw invalid_argument("The parameter \"systemLogic\" is nullptr");
		if (systemInput == nullptr) throw invalid_argument("The parameter \"systemInput\" is nullptr");
	}

	void EntityFactory::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));
	}

	shared_ptr<IEntity> EntityFactory::CreateEntity(shared_ptr<EntityEvent> event)
	{
		// Create the entity using the entity factory provided by the user
		auto entity = m_GameEntityFactory->Create(event);
		if (entity == nullptr)
			throw runtime_error("The entity named \"" + StringUtil::ToStr(event->GetName()) + "\" returned a nullptr from the EntityFactory provided by the game");

		// Register the component to its proper system
		for (auto& component : entity->GetComponents())
		{
			component->Init();
			switch (component->GetType())
			{
			case IComponent::Type::Audio:
				m_SystemAudio->Add(component);
				break;
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
		m_Entities.emplace(event->GetEntityId(), entity);
		return m_Entities.at(event->GetEntityId());
	}

	void EntityFactory::Update()
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
				CreateEntity(ev);
				break;
			case EntityEvent::Type::Delete:
				DeleteEntity(ev->GetName(), ev->GetEntityId());
				break;
			}
		}
	}

	void EntityFactory::DeleteEntity(const wstring &name, int entityId)
	{
		auto entity = m_Entities.at(entityId);
		for (auto component : entity->GetComponents())
		{
			if (component->GetType() == IComponent::Type::Audio)
				m_SystemAudio->Remove(component);
			if (component->GetType() == IComponent::Type::Graphic)
				m_SystemGraphic->Remove(component);
			if (component->GetType() == IComponent::Type::Logic)
				m_SystemLogic->Remove(component);
			if (component->GetType() == IComponent::Type::Input)
				m_SystemInput->Remove(component);
			component->Shutdown();
		}
		m_Entities.erase(entityId);
		m_GameEntityFactory->Delete(entityId);
	}
}
