#pragma once
#include "stdafx.h"
namespace Engine
{

enum class LogLevel
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_NONE
};

class Logger
{
public:
	void Log(const sf::String &msg, LogLevel level) const;
	void SetLogLevel(LogLevel level);
	void Init();
private:
	LogLevel m_logLevel;
};
}