#pragma once
#include <Engine\IComponent.h>
using namespace Engine;
namespace Game
{
	class MushroomInputComponent : public IComponent
	{
	public:
		~MushroomInputComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomInputComponent"; }
		Type GetType() const override { return IComponent::Type::Input; }
	};

	class MushroomLogicComponent : public IComponent
	{
	public:
		~MushroomLogicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomLogicComponent"; }
		Type GetType() const override { return IComponent::Type::Logic; }
	};

	class MushroomGraphicComponent : public IComponent
	{
	public:
		~MushroomGraphicComponent() = default;
		void Init() override {};
		void Shutdown() override {};
		void Update(float dt) override;

		wstring GetName() const override { return L"MushroomGraphicComponent"; }
		Type GetType() const override { return IComponent::Type::Graphic; }
	};
}