#pragma once

namespace Engine
{
	class System
	{
	public:
		virtual ~System() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
	};
}