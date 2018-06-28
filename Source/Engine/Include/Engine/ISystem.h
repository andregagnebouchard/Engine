#pragma once

namespace Engine
{
	class ISystem
	{
	public:
		virtual ~ISystem() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
	};
}