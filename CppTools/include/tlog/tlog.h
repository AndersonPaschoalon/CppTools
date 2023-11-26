/**
#ifndef __T_LOG__
#define __T_LOG__ 1

#include <cstring>
#include <cstdio>
#include <mutex>


#define TLOG_APPENDER_FILE_NAME_SIZE 512


namespace TLog
{

    enum TLogAppenderType{
        CONSOLE_APPENDER,
        FILE_APPENDER,
        BOTH_APPENDER
    };

    enum TLogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    extern TLogLevel gTLogLevel;
    extern TLogAppenderType gTAppenderType;
    extern char gTLogFileName[TLOG_APPENDER_FILE_NAME_SIZE];
    extern char gTLogFileAppenderSeparator;
    std::mutex gTLogFileMutex;

    #define TLOG(level, format, ...) \
        do { \
            if (level >= TLog::gTLogLevel) { \
                if (TLog::gTAppenderType == TLog::TLogAppenderType::CONSOLE_APPENDER ) {\
                    printf(format "\n", ##__VA_ARGS__); \
                } else if (TLog::gTAppenderType == TLog::TLogAppenderType::FILE_APPENDER ) {\
                    TLog::TLoggerAppendToFile(level, __FILE__, __FUNCTION__, TLog::TLoggerStringFormatVariadic(format, ##__VA_ARGS__).c_str());\
                } else if (TLog::gTAppenderType == TLog::TLogAppenderType::BOTH_APPENDER ) {\
                    printf(format "\n", ##__VA_ARGS__); \
                    TLog::TLoggerAppendToFile(level, __FILE__, __FUNCTION__, TLog::TLoggerStringFormatVariadic(format, ##__VA_ARGS__).c_str());\
                }\
            } \
        } while(0)

    void TLoggerConfigure(TLog::TLogLevel loggerLevel, TLog::TLogAppenderType appenderType, const char* logFileName = "", const char fileAppenderSeparator = '\t');

    std::string TLoggerStringFormatVariadic(const char* format, ...);

    void TLoggerAppendToFile(TLog::TLogLevel logLevel, const char* sourceName, const char* functionName, const char* logMsg);


}




#endif // __T_LOG__
*/