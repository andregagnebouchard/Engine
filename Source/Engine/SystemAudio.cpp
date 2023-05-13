#include "stdafx.h"
#include "SystemAudio.h"
#include "ResourceCache.h"
#include <Engine\IComponent.h>
#include "EventDefinition.h"
#include "StringUtil.h"
#include <SFML/Audio.hpp>
#include <memory>
namespace Engine
{
	SystemAudio::SystemAudio(shared_ptr<ResourceCache> resourceCache) :
		m_ResourceCache(resourceCache)
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::AUDIO)));
	}

	void SystemAudio::Init()
	{
	}

	void SystemAudio::Shutdown()
	{
		Messager::Detach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::AUDIO)));
	}

	void SystemAudio::Update()
	{
		// Update all components first so they can fire their sound event
		for (auto& component : m_Components)
			component.second->Update();

		while (!m_MsgQueue.Empty())
		{
			shared_ptr<Event>& event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			if (event->GetType() == Event::Type::Audio)
				HandleAudioEvent(dynamic_pointer_cast<AudioEvent>(event));
			else
				throw invalid_argument("Unknown sound event received by SystemAudio");
		}
	}

	void SystemAudio::Add(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it != m_Components.end())
			throw invalid_argument("The component is already added in SystemSound");

		m_Components[component->GetId()] = component;
	}

	void SystemAudio::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		auto it = m_Components.find(component->GetId());
		if (it == m_Components.end())
			throw invalid_argument("The component is not in SystemSound");

		m_Components.erase(component->GetId());
	}

	void SystemAudio::HandleAudioEvent(shared_ptr<AudioEvent> event)
	{
		Resource* resource = m_ResourceCache->GetResource((event->GetResourceName()));
		if (resource->GetType() != Resource::Type::Audio)
			throw invalid_argument("A non-audio resource was asked to be played: \"" + StringUtil::ToStr(resource->GetName()));

		AudioResource* audioResource = dynamic_cast<AudioResource*>(resource);

		audioResource->GetSound()->play();
	}
}