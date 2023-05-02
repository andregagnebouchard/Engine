#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\WorldGrid.h>
using namespace Engine;
namespace Game
{
	class GridLogicComponent : public IComponent
	{
	public:
		GridLogicComponent(int entityId, WorldGrid *grid);
		~GridLogicComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"GridLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		void HandleEntityEvent(shared_ptr<EntityEvent> ev);
		void HandleCreateEntityEvent(shared_ptr<EntityEvent> ev);
		void HandleDeleteEntityEvent(shared_ptr<EntityEvent> ev);
		void HandleMoveEvent(shared_ptr<LogicEvent> event);
		MessageQueue m_MsgQueue;
		unordered_map<int, CellLocation> m_EntityToLocation; // I don't like using the heap here
		WorldGrid* m_Grid; // Owner is entity factory
		int m_EntityId;
	};

	class GridInputComponent : public IComponent
	{
	public:
		GridInputComponent(int entityId);
		~GridInputComponent() = default;
		void Init() override;
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"GridInputComponent"; }
		Type GetType() const override { return IComponent::Type::Input; }
		int GetId() const override { return m_EntityId; };
	private:
		MessageQueue m_MsgQueue;
		int m_EntityId;
	};
}