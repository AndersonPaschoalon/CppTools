#ifndef __PLOG_MACROS_H_
#define __PLOG_MACROS_H_ 1

#include <cstdlib>
#include <string.h>
#include <string>
#include <iostream>
#include <plog/Init.h>
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>


// TODO: 
// Fazer uma macro que toma como parametro um arquivo .ini, e faz a leitura dos demais parametros dele
// #define PLOG_INIT(plogConfigIni)


#define PLOG_INIT(logLevel, logfilename, maxSize, maxFiles)\
		if(logfilename)\
		{ \
			strcpy(_fileName, logfilename);\
			static plog::RollingFileAppender<plog::CsvFormatter> fileAppender(logfilename,\
					maxSize, maxFiles);\
			static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;\
			plog::init(plog::logLevel, &fileAppender).addAppender(&consoleAppender); \
		}\
		else\
		{\
			static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;\
			plog::init(plog::logLevel, &consoleAppender);\
			LOG_ERROR  << "[" << __FILE__ << "] " << "Can't find env variable SIMITAR_LOGFILE";\
		}

#define PLOG_NONE LOG_NONE  << "[" << __FILE__ << "] "
#define PLOG_FATAL LOG_FATAL  << "[" << __FILE__ << "] "
#define PLOG_ERROR LOG_ERROR  << "[" << __FILE__ << "] "
#define PLOG_WARN LOG_WARNING  << "[" << __FILE__ << "] "
#define PLOG_INFO LOG_INFO  << "[" << __FILE__ << "] "
#define PLOG_DEBUG LOG_DEBUG  << "[" << __FILE__ << "] "
#define PLOG_VERBOSE LOG_VERBOSE  << "[" << __FILE__ << "] "

#endif // __PLOG_MACROS_H_