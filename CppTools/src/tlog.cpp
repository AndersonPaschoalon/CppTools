/**
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <cstdarg>
#include <vector>
#include "tlog.h"


TLog::TLogLevel gTLogLevel = TLog::TLogLevel::DEBUG;
TLog::TLogAppenderType gTAppenderType =  TLog::TLogAppenderType::CONSOLE;
char gTLogFileName[TLOG_APPENDER_FILE_NAME_SIZE] = {'\0'};
char TLog::gTLogFileAppenderSeparator = '\t';

void TLog::TLoggerConfigure(TLog::TLogLevel loggerLevel, TLog::TLogAppenderType appenderType, const char *logFileName, const char fileAppenderSeparator)
{
    gTLogLevel = loggerLevel;
    gTAppenderType = appenderType;
    gTLogFileAppenderSeparator = fileAppenderSeparator;
    if(logFileName != nullptr && strcmp(logFileName, "") != 0)
    {    
        strcpy(gTLogFileName, logFileName);
    }

}

std::string TLog::TLoggerStringFormatVariadic(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Determine the length of the resulting string
    va_list args_copy;
    va_copy(args_copy, args);
    const int length = std::vsnprintf(nullptr, 0, format, args_copy);
    va_end(args_copy);

    // Create a buffer and format the string
    std::vector<char> buffer(length + 1); // +1 for null-terminator
    std::vsnprintf(buffer.data(), buffer.size(), format, args);
    va_end(args);

    return std::string(buffer.data());
}

void TLog::TLoggerAppendToFile(TLogLevel logLevel, const char *sourceName, const char *functionName, const char *logMsg)
{
    if (gTLogFileName == nullptr || gTLogFileName[0] == '\0') {
        // If gLogFileName is empty or null, do nothing
        return;
    }

    // Convert the log level to a string
    std::string logLevelStr;
    switch (logLevel) 
    {
        case TLog::DEBUG: logLevelStr = "DEBUG"; break;
        case TLog::INFO: logLevelStr = "INFO"; break;
        case TLog::WARN: logLevelStr = "WARN"; break;
        case TLog::ERROR: logLevelStr = "ERROR"; break;
        default: logLevelStr = "UNKNOWN"; break;
    }

    // Get the current timestamp
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::system_clock::to_time_t(now);

    std::stringstream logEntry;
    logEntry << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S")
                << gTLogFileAppenderSeparator
                << std::this_thread::get_id()
                << gTLogFileAppenderSeparator
                << logLevelStr
                << gTLogFileAppenderSeparator
                << sourceName
                << gTLogFileAppenderSeparator
                << functionName
                << gTLogFileAppenderSeparator
                << logMsg;

    // Protect the write process with a mutex
    std::lock_guard<std::mutex> lock(gTLogFileMutex);

    // Open the log file in append mode
    std::ofstream logFile(gTLogFileName, std::ios::app);
    if (logFile.is_open()) 
    {
        logFile << logEntry.str() << '\n';
        logFile.close();
    } 
}

*/