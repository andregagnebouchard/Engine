#pragma once
#include "stdafx.h"
#include <Engine\Export.h>

namespace Engine
{
	class EXPORT System
	{
	public:
		virtual ~System() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update() = 0;
	};
}