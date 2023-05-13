#include "stdafx.h"
#include "Logger.h"
using namespace Engine;
void Logger::Init()
{
	log4cplus::Initializer initializer;

	log4cplus::BasicConfigurator config;
	config.configure();

	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Engine"));
	log4cplus::SharedFileAppenderPtr loggerFileAppender(new log4cplus::RollingFileAppender(LOG4CPLUS_TEXT("log//Engine.log"), 5 * 1024, 5, false, true));
	logger.addAppender(log4cplus::SharedAppenderPtr(loggerFileAppender.get()));
	LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Logger initialized"));
}

void Logger::Log(const sf::String &msg, Level level)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Engine"));

	switch (level)
	{
		case Level::Debug:
		{
			LOG4CPLUS_DEBUG(logger, msg.toWideString());
			break;
		}
		case Level::Info:
		{
			LOG4CPLUS_INFO(logger, msg.toWideString());
			break;
		}
		case Level::Warning:
		{
			LOG4CPLUS_WARN(logger, msg.toWideString());
			break;
		}
		case Level::Error:
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

void Logger::SetLogLevel(Level level)
{
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Engine"));
	switch (level)
	{
		case Level::Debug:
		{
			logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
			break;
		}
		case Level::Info:
		{
			logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
			break;
		}
		case Level::Warning:
		{
			logger.setLogLevel(log4cplus::WARN_LOG_LEVEL);
			break;
		}
		case Level::Error:
		{
			logger.setLogLevel(log4cplus::ERROR_LOG_LEVEL);
			break;
		}
	}
}
