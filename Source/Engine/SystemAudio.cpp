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
	SystemAudio::SystemAudio(const shared_ptr<ResourceCache> resourceCache) :
		m_ResourceCache(resourceCache)
	{
	}

	void SystemAudio::Init()
	{
		Messager::Attach(m_MsgQueue.GetCallback(), Event::Key(static_cast<int>(EventDefinition::Id::AUDIO)));
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
			const shared_ptr<Event>& event = m_MsgQueue.Front();
			m_MsgQueue.Pop();

			if (event->GetType() == Event::Type::Audio)
				HandleAudioEvent(dynamic_pointer_cast<AudioEvent>(event));
			else
				throw invalid_argument("Unknown sound event received by SystemAudio");
		}
	}

	void SystemAudio::Add(const shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.emplace(component->GetId(), component);
	}

	void SystemAudio::Remove(shared_ptr<IComponent> component)
	{
		if (component == nullptr)
			throw invalid_argument("The parameter \"Component\" is nullptr");

		m_Components.erase(component->GetId());
	}

	void SystemAudio::HandleAudioEvent(const shared_ptr<AudioEvent> event) const
	{
		Resource* resource = m_ResourceCache->GetResource((event->GetResourceName()));
		if (resource->GetType() != Resource::Type::Audio)
			throw invalid_argument("A non-audio resource was asked to be played: \"" + StringUtil::ToStr(resource->GetName()));

		const AudioResource* const audioResource = dynamic_cast<AudioResource*>(resource);

		audioResource->GetSound()->play();
	}
}