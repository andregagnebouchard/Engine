#pragma once
#include <Engine\IEntityFactory.h>
#include <Engine\IComponent.h>
#include <Engine\SystemGraphic.h>
#include <Engine\SystemInput.h>
#include <Engine\SystemLogic.h>
#include <Engine\SystemAudio.h>
#include "Entity.h"
#include "EngineEntityFactory.h"
#include "StringUtil.h"
#include "EventDefinition.h"
using namespace std;
namespace Engine
{
	EngineEntityFactory::EngineEntityFactory(const shared_ptr<IGameEntityFactory> gameEntityFactory, const shared_ptr<SystemGraphic> systemGraphic, const shared_ptr<SystemLogic> systemLogic, const shared_ptr<SystemInput> systemInput, const shared_ptr<SystemAudio> systemAudio) :
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

	void EngineEntityFactory::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));
	}

	void EngineEntityFactory::Shutdown()
	{
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::DELETE_ENTITY)));
	}

	shared_ptr<Entity> EngineEntityFactory::CreateEntity(const shared_ptr<EntityEvent> event)
	{
		// Create the entity using the entity factory provided by the user
		const shared_ptr<Engine::Entity> entity = m_GameEntityFactory->Create(event);
		if (entity == nullptr)
			throw runtime_error("The entity named \"" + StringUtil::ToStr(event->GetName()) + "\" returned a nullptr from the EntityFactory provided by the game");

		// Register the component to its proper system
		for (const auto& component : entity->GetComponents())
		{
			component->Init();
			const IComponent::Type type = component->GetType();
			if(type == IComponent::Type::Logic) // Most common one checked first
				m_SystemLogic->Add(component);
			else if(type == IComponent::Type::Graphic)
				m_SystemGraphic->Add(component);
			else if (type == IComponent::Type::Input)
				m_SystemInput->Add(component);
			else if (type == IComponent::Type::Audio)
				m_SystemAudio->Add(component);
			else
				throw runtime_error("Unknown component type");
		}
		m_Entities.emplace(event->GetEntityId(), entity);
		return m_Entities.at(event->GetEntityId());
	}

	void EngineEntityFactory::Update()
	{
		while (!m_MsgQueue.Empty())
		{
			const shared_ptr<Event> &event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			if (event->GetType() != Event::Type::Entity)
				throw invalid_argument("Unknown event type handled by EntityFactory");

			const auto ev = dynamic_pointer_cast<EntityEvent>(event);
			if(ev->GetActionType() == EntityEvent::Type::Create)
				CreateEntity(ev);
			else if(ev->GetActionType() == EntityEvent::Type::Delete)
				DeleteEntity(ev->GetName(), ev->GetEntityId());
		}
	}

	void EngineEntityFactory::DeleteEntity(const wstring &name, int entityId)
	{
		const auto entity = m_Entities.at(entityId);
		for (const auto component : entity->GetComponents())
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
