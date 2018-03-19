#pragma once
#include "stdafx.h"
namespace Engine
{
	class Logger
	{
	public:
		enum class Level
		{
			Debug,
			Info,
			Warning,
			Error,
			None
		};

		static void Log(const sf::String &msg, Level level);
		static void SetLogLevel(Level level);
		static void Init();
	private:
		static Level m_Level;
	};
}