#include "stdafx.h"
#include "Logger.h"
using namespace Engine;
//=================================================================================================
void Logger::Init()
{
	log4cplus::Initializer initializer;

	log4cplus::BasicConfigurator config;
	config.configure();

	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Engine"));
	log4cplus::SharedFileAppenderPtr loggerFileAppender(NEW log4cplus::RollingFileAppender(LOG4CPLUS_TEXT("log//Engine.log"), 5 * 1024, 5, false, true));
	logger.addAppender(log4cplus::SharedAppenderPtr(loggerFileAppender.get()));
	LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Logger initialized"));
}
//=================================================================================================
void Logger::Log(const sf::String &msg, LogLevel level) const
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Engine"));

	switch (level)
	{
		case LogLevel::LOG_DEBUG :
		{
			LOG4CPLUS_DEBUG(logger, msg.toWideString());
			break;
		}
		case LogLevel::LOG_INFO:
		{
			LOG4CPLUS_INFO(logger, msg.toWideString());
			break;
		}
		case LogLevel::LOG_WARNING:
		{
			LOG4CPLUS_WARN(logger, msg.toWideString());
			break;
		}
		case LogLevel::LOG_ERROR:
		{
			LOG4CPLUS_ERROR(logger, msg.toWideString());
			break;
		}
		default:
		{
			throw std::exception("Invalid log level");
		}
	}
}
//=================================================================================================
void Logger::SetLogLevel(LogLevel level)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Engine"));
	switch (level)
	{
		case LogLevel::LOG_DEBUG:
		{
			logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
			break;
		}
		case LogLevel::LOG_INFO:
		{
			logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
			break;
		}
		case LogLevel::LOG_WARNING:
		{
			logger.setLogLevel(log4cplus::WARN_LOG_LEVEL);
			break;
		}
		case LogLevel::LOG_ERROR:
		{
			logger.setLogLevel(log4cplus::ERROR_LOG_LEVEL);
			break;
		}
	}
}
//=================================================================================================