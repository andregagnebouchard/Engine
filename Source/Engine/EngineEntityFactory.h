#pragma once
#include <Engine/Messager.h>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class IComponentFactory;
	class ISystemGraphic;
	class ISystemLogic;
	class ISystemInput;
	class SystemAudio;
	class IGameEntityFactory;
	class EntityEvent;
	class Entity;
	class EngineEntityFactory
	{
	public:
		// The systems are required to register in order to register the components to them
		EngineEntityFactory(const shared_ptr<IGameEntityFactory> gameEntityFactory, const shared_ptr<SystemGraphic> systemGraphic, const shared_ptr<SystemLogic> systemLogic, const shared_ptr<SystemInput> systemInput, const shared_ptr<SystemAudio> systemAudio);

		void Init();
		void Shutdown();
		void Update();
		void OnEvent(const shared_ptr<Event> event);
	private:
		shared_ptr<Entity> CreateEntity(const shared_ptr<EntityEvent> event);
		void DeleteEntity(const wstring& name, int entityId);

		const shared_ptr<IGameEntityFactory> m_GameEntityFactory;
		const shared_ptr<SystemGraphic> m_SystemGraphic;
		const shared_ptr<SystemLogic> m_SystemLogic;
		const shared_ptr<SystemInput> m_SystemInput;
		const shared_ptr<SystemAudio> m_SystemAudio;
		unordered_map<int, shared_ptr<Engine::Entity>> m_Entities;
		const function<void(shared_ptr<Event>)> m_EventCallback;
		queue<shared_ptr<Event>> m_MsgQueue;
	};
}
