// https://sourceforge.net/p/log4cplus/wiki/CodeExamples/
#include "stdafx.h"
#include "CppUnitTest.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace EngineComponentTests
{
	TEST_CLASS(Testlog4cplus)
	{
	public:

		TEST_METHOD(Uselog4cplus)
		{
			// Initialization and deinitialization.
			log4cplus::Initializer initializer;

			log4cplus::BasicConfigurator config;
			config.configure();

			log4cplus::Logger logger = log4cplus::Logger::getInstance(
			LOG4CPLUS_TEXT("main"));
			LOG4CPLUS_WARN(logger, LOG4CPLUS_TEXT("Hello, World!"));
		}
	};
}