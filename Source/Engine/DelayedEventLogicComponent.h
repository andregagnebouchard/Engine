#pragma once
#include <Engine/Event.h>
#include <Engine/IComponent.h>
using namespace std;
namespace Engine
{
	// This class with throw a logic event with the input key after X ticks
	// I have a feeling that this component would be easier if the same logic component could be used to schedule multiple events, instead
	// of having to create one instance for each schedule
	class DelayedEventLogicComponent : public IComponent
	{
	public:
		DelayedEventLogicComponent(int entityId, int delayTick, const Event::Key &keyToEmit);
		virtual ~DelayedEventLogicComponent() = default;

		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		wstring GetName() const override { return L"DelayedEventLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		const int m_EntityId;
		const int m_DelayTick;
		int m_TickCounter;
		const Event::Key m_KeyToEmit;
	};
}