#include "../plog/Log.h"
#include "../plog/Initializers/RollingFileInitializer.h"
#include "../plog/Appenders/ColorConsoleAppender.h"
#include "../plog/Formatters/MessageOnlyFormatter.h"


int inline plog_easy_init(plog::Severity logLevel, const char* logFile,  size_t maxFileSize = 800000, int maxFiles = 5)
{
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(logFile, maxFileSize, maxFiles);
    static  plog:: ColorConsoleAppender<plog::MessageOnlyFormatter> consoleAppender;
    plog::init(logLevel, &fileAppender).addAppender(&consoleAppender);   
}

#ifndef FLAG_PLOG_DEBUG

#define _PLOG_NONE      PLOG_NONE  
#define _PLOG_FATAL     PLOG_NONE 
#define _PLOG_ERROR     PLOG_NONE 
#define _PLOG_WARN      PLOG_NONE  
#define _PLOG_INFO      PLOG_NONE  
#define _PLOG_DEBUG     PLOG_NONE 
#define _PLOG_VERBOSE   PLOG_NONE 


#else

#define _PLOG_NONE PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_FATAL PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_ERROR PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_WARN PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_INFO PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_DEBUG PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_VERBOSE PLOG_NONE  << "[" << __FILE__ << "] "

#endif