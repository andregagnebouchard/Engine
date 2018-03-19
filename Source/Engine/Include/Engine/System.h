#pragma once
#include "stdafx.h"

namespace Engine
{
	class System
	{
	public:
		virtual ~System() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;
	};
}