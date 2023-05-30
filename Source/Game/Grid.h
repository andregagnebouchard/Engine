#pragma once
#include <Engine\IComponent.h>
#include <Engine\Messager.h>
#include <Engine\IGameLogicEvent.h>
#include <Engine\Grid.h>
namespace Game
{
	struct DebugState;

	class GridLogicComponent : public Engine::IComponent
	{
	public:
		GridLogicComponent(int entityId, Engine::Grid *grid);
		~GridLogicComponent() = default;
		void Init() override;
		void Shutdown() override;
		void OnEvent(const shared_ptr<Engine::Event> event);
		void Update() override;

		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		void HandleEntityEvent(const shared_ptr<Engine::EntityEvent> ev);
		void HandleCreateEntityEvent(const shared_ptr<Engine::EntityEvent> ev);
		void HandleDeleteEntityEvent(const shared_ptr<Engine::EntityEvent> ev);
		void HandleMoveEvent(const shared_ptr<Engine::LogicEvent> event);
		const function<void(shared_ptr<Engine::Event>)> m_EventCallback;
		unordered_map<int, Engine::Grid::CellLocation> m_EntityToLocation; // I don't like using the heap here
		Engine::Grid* m_Grid; // Owner is entity factory
		int m_EntityId;
	};

	class GridGraphicComponent : public Engine::IComponent
	{
	public:
		GridGraphicComponent(int entityId, const Engine::Grid* grid, const DebugState* state);
		~GridGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		Type GetType() const override { return IComponent::Type::Graphic; }
		int GetId() const override { return m_EntityId; };
	private:
		const Engine::Grid* m_Grid; // Owner is entity factory
		int m_EntityId;
		const DebugState* m_DebugState;
	};
}