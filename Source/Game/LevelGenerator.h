#pragma once
#include <Engine\IComponent.h>
#include "Entity.h"
using namespace Engine;
namespace Game
{
	class LevelGeneratorLogicComponent : public IComponent
	{
	public:
		LevelGeneratorLogicComponent(int entityId);
		~LevelGeneratorLogicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update() override;

		void GenerateSmallDots();
		void GenerateBigDots();
		void GenerateGhost();
		void DeleteItself();
		wstring GetName() const override { return L"LevelGeneratorLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		int m_EntityId;
	};
}