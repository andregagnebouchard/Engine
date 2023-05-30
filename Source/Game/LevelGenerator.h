#pragma once
#include <Engine\IComponent.h>
#include "EntityTypes.h"
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

		void GenerateSmallDots() const;
		void GenerateBigDots() const;
		void GenerateGhost() const;
		void DeleteItself() const;
		Type GetType() const override { return IComponent::Type::Logic; }
		int GetId() const override { return m_EntityId; };
	private:
		const int m_EntityId;
	};
}