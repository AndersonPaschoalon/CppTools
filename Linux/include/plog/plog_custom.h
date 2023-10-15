#include "../plog/Log.h"
#include "../plog/Initializers/RollingFileInitializer.h"
#include "../plog/Appenders/ColorConsoleAppender.h"


int inline plog_easy_init(plog::Severity logLevel, const char* logFile,  size_t maxFileSize = 800000, int maxFiles = 5)
{
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(logFile, maxFileSize, maxFiles);
    static  plog:: ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(logLevel, &fileAppender).addAppender(&consoleAppender);   
}


#define _PLOG_NONE PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_FATAL PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_ERROR PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_WARN PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_INFO PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_DEBUG PLOG_NONE  << "[" << __FILE__ << "] "
#define _PLOG_VERBOSE PLOG_NONE  << "[" << __FILE__ << "] "