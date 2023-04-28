#include "stdafx.h"
#include "SystemPhysic.h"
#include "Messager.h"
#include <Engine\IComponent.h>
#include "Box2DPhysic.h"
#include "StringUtil.h"
#include "EventDefinition.h"
namespace Engine
{
	SystemPhysic::SystemPhysic(shared_ptr<ICollisionLogic> collisionLogic, shared_ptr<Box2DPhysic> box2DPhysic) :
		m_CollisionLogic(collisionLogic),
		m_Box2DPhysic(box2DPhysic)
	{
	}

	void SystemPhysic::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
		// Attach the callback to the collision logic here
	}

	void SystemPhysic::Shutdown()
	{
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::CREATE_ENTITY)));
	}

	void SystemPhysic::Update(float dt)
	{
		// Update all components
		for (auto& component : m_Components)
			component.second->Update(dt);

		while (!m_MsgQueue.Empty())
		{
			shared_ptr<Event>& event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			if (event->GetType() != Event::Type::Entity)
				throw invalid_argument("Unknown event type handled by PhysicSystem");

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

		m_Box2DPhysic->GetWorld()->Step(dt, 1, 1);
	}

	void SystemPhysic::CreateEntity(const wstring& entityName)
	{
		m_Box2DPhysic->Create();
	}
	void SystemPhysic::DeleteEntity(const wstring& entityName)
	{

	}

	void SystemPhysic::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is already added in SystemPhysic");

		m_Components[component->GetId()] = component;
	}

	void SystemPhysic::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it == m_Components.end())
			throw invalid_argument("The component \"" + StringUtil::ToStr(component->GetName()) + "\" with id \"" + to_string(component->GetId()) + "\" is not in SystemPhysic");

		m_Components.erase(component->GetId());
	}
}