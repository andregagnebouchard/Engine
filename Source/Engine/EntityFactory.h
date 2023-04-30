#pragma once
#include <Engine/Messager.h>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;
namespace Engine
{
	class IEntity;
	class IComponentFactory;
	class ISystemGraphic;
	class ISystemLogic;
	class ISystemInput;
	class ISystemAudio;
	class IEntityFactory;
	class EntityEvent;
	class EntityFactory
	{
	public:
		// The systems are required to register in order to register the components to them
		EntityFactory(shared_ptr<IEntityFactory> gameEntityFactory, shared_ptr<ISystemGraphic> systemGraphic, shared_ptr<ISystemLogic> systemLogic, shared_ptr<ISystemInput> systemInput, shared_ptr<ISystemAudio> systemAudio);

		void Init();
		void Update(float dt);
	private:
		shared_ptr<IEntity> CreateEntity(shared_ptr<EntityEvent> event);
		void DeleteEntity(const wstring& name, int entityId);

		shared_ptr<IEntityFactory> m_GameEntityFactory;
		shared_ptr<ISystemGraphic> m_SystemGraphic;
		shared_ptr<ISystemLogic> m_SystemLogic;
		shared_ptr<ISystemInput> m_SystemInput;
		shared_ptr<ISystemAudio> m_SystemAudio;
		unordered_map<int, shared_ptr<IEntity>> m_Entities;
		MessageQueue m_MsgQueue;
	};
}
