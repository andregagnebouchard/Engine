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
	class ISystemAudio;
	class IGameEntityFactory;
	class EntityEvent;
	class EngineEntityFactory
	{
	public:
		// The systems are required to register in order to register the components to them
		EngineEntityFactory(const shared_ptr<IGameEntityFactory> gameEntityFactory, const shared_ptr<ISystemGraphic> systemGraphic, const shared_ptr<ISystemLogic> systemLogic, const shared_ptr<ISystemInput> systemInput, const shared_ptr<ISystemAudio> systemAudio);

		void Init();
		void Shutdown();
		void Update();
	private:
		shared_ptr<Entity> CreateEntity(const shared_ptr<EntityEvent> event);
		void DeleteEntity(const wstring& name, int entityId);

		const shared_ptr<IGameEntityFactory> m_GameEntityFactory;
		const shared_ptr<ISystemGraphic> m_SystemGraphic;
		const shared_ptr<ISystemLogic> m_SystemLogic;
		const shared_ptr<ISystemInput> m_SystemInput;
		const shared_ptr<ISystemAudio> m_SystemAudio;
		unordered_map<int, shared_ptr<Engine::Entity>> m_Entities;
		MessageQueue m_MsgQueue;
	};
}
