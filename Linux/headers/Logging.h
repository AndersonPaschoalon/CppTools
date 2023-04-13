//
// Author       Wild Coast Solutions
//              David Hamilton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.
//
// This file contains an implementation of a simple logging framework.
// This works by maintaining a single Logger class that has various 
// message destinations that are mapped to the message level (Info, Debug, Warning, Error)
// E.g. for an Info message the Logger sends that message to all destinations
// registered to handle Info. Valid destinations are File, Stdout and Stderr.
//
// Project url: https://github.com/WildCoastSolutions/Logging


#ifndef WILD_LOGGING_LOGGING_H
#define WILD_LOGGING_LOGGING_H 1

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <list>
#include <chrono>
#include <iomanip>
#include <time.h>
#include <mutex>

namespace Wild
{
	namespace Logging
	{
        // Possible destinations for log messages
        enum class DestinationType{
            Stdout,
            Stderr,
            File
        };

        // Levels supported for log messages
        enum class Level{
            Info,
            Debug,
            Warning,
            Error
        };

        // Overload to print out Level enum
        static std::ostream& operator << (std::ostream& os, const Level& l)
        {
            switch (l)
            {
            case Level::Info:       os << "Info"; break;
            case Level::Debug:      os << "Debug"; break;
            case Level::Warning:    os << "Warning"; break;
            case Level::Error:      os << "Error"; break;
            }
            return os;
        }

        // Base class for log message destinations, all children must implement Write
        class Destination
        {
        public:
            virtual void Write(const std::string &s) = 0;
        protected:
            std::mutex destinationMutex;    // Protect destinations from being written to at the same time
        };

        // File destination, writes out messages to log file
        class FileDestination : public Destination
        {
        public:

            FileDestination(const std::string &path)
            {
                out.open(path.c_str(), std::ios::out);
                if (!out.is_open()) throw std::runtime_error("Couldn't open file named " + path);
            }

            ~FileDestination()
            {
                out.close();
            }

            void Write(const std::string &s)
            {
                // Access to the output for this destination must be thread safe
                std::lock_guard<std::mutex> lock(destinationMutex);
                out << s << std::flush;
            }

            std::ofstream out;
        };

        // Stdout destination
        class Stdout : public Destination
        {
        public:
            void Write(const std::string &s)
            {
                // Access to the output for this destination must be thread safe
                std::lock_guard<std::mutex> lock(destinationMutex);
                std::cout << s;
            }
        };

        // Stderr destination
        class Stderr : public Destination
        {
        public:
            void Write(const std::string &s)
            {
                // Access to the output for this destination must be thread safe
                std::lock_guard<std::mutex> lock(destinationMutex);
                std::cerr << s;
            }
        };

        // types for adding extra info to a log message in the form of name value pairs
        typedef std::pair<std::string, std::string> I;
        typedef std::list<I> InfoBlob;
        

        // Generates timestamps for log messages
        static std::string Timestamp()
        {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::stringstream s;
 
#ifdef _WIN32
            std::tm tm;
            gmtime_s(&tm, &now);
            s << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
#else
            // only gcc > 5 supports put_time, so use alternate method
            std::tm *tm = gmtime(&now);
            char buffer[256];
            strftime(buffer, 256, "%Y-%m-%dT%H:%M:%SZ", tm);
            s << buffer;
#endif
           
            return s.str();
        }

        // Class that drives the logging process, maintains destinations and routes messages to them.
        // Not designed to be directly used by the user application.
        class Logger
        {
        public:
            Logger() {}
            static Logger& instance()
            {
                static Logger instance;
                return instance;
            }

            // Make sure we clean up all destinations we know about, this ensure we close any open files
            ~Logger()
            {
                Shutdown();
            }

            void Shutdown()
            {
                for (auto &destinations : m_destinations)
                {
                    for (std::shared_ptr<Destination> &i : destinations.second)
                    {
                        i.reset();
                    }
                }
            }

            // Adds a destination that prints messages to stdout
            //
            //      levels  specifies the log levels that should be passed to this destination  
            void AddStdoutDestination(std::initializer_list<Level> levels = { Level::Info, Level::Warning, Level::Error, Level::Debug })
            {
                auto destination = std::shared_ptr<Destination>(new Stdout());
                for (auto level : levels)
                {
                    m_destinations[level].push_back(destination);
                }
            }

            // Adds a destination that prints messages to stderr
            //
            //      levels  specifies the log levels that should be passed to this destination
            void AddStderrDestination(std::initializer_list<Level> levels = { Level::Info, Level::Warning, Level::Error, Level::Debug })
            {
                auto destination = std::shared_ptr<Destination>(new Stderr());
                for (auto level : levels)
                {
                    m_destinations[level].push_back(destination);
                }
            }

            // Adds a destination that prints messages to a file
            //
            //      path    name of file to write to
            //      levels  specifies the log levels that should be passed to this destination
            void AddFileDestination(const std::string &path, std::initializer_list<Level> levels = { Level::Info, Level::Warning, Level::Error, Level::Debug })
            {
                auto destination = std::shared_ptr<Destination>(new FileDestination(path));
                for (auto level : levels)
                {
                    m_destinations[level].push_back(destination);
                }
            }

            // Sets the global debug level
            void SetDebugLevel(int debugLevel)
            {
                m_debugLevel = debugLevel;
            }

            int GetDebugLevel()
            {
                return m_debugLevel;
            }

            // Log function that drives the logging process - all log messages will come here.
            // Formats the message and info, adding timestamp, and maps the level to the 
            // destinations for outputting.
            void Log(
                Level level,
                const std::string &doing,
                const std::string &result,
                const InfoBlob &blob)
            {
                std::stringstream s;
                s << Timestamp() << " " << level << ": " << doing;
                if (result.size() > 0)
                    s << ", " << result << ".";
                else
                    s << ".";
                if (blob.size() > 0)
                {
                    s << " Data {";
                    auto i = blob.begin();
                    while (i != blob.end())
                    {
                        s << i->first << ": " << i->second;
                        i++;
                        if (i != blob.end()) s << ", ";
                    }
                    s << "}";
                }

                s << std::endl;

                auto destinations = m_destinations[level];
                for (auto &i : destinations)
                {
                    i->Write(s.str());
                }
            }

            // Checks the debug level before logging
            void Debug(
                int debugLevel,
                const std::string &doing,
                const std::string &result,
                const InfoBlob &blob)
            {
                if (debugLevel <= m_debugLevel)
                    Log(Level::Debug, doing, result, blob);
            }

        private:

            // Maps Level to list of Destinations
            std::map<Level, std::vector<std::shared_ptr<Destination>>> m_destinations;
            int m_debugLevel;
        };

        // Helper function for level specific log functions e.g. Info
        static void Log(
            Level level,
            const std::string &doing,
            const std::string &result,
            const std::initializer_list<I> &data = {})
        {
            Logger::instance().Log(level, doing, result, data);
        }

        // Helper function for level specific log functions e.g. Info
        static void Log(
            Level level,
            const std::string &doing,
            const std::string &result,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            // Merge blob and data
            InfoBlob b = blob;
            b.insert(b.end(), data);
            Logger::instance().Log(level, doing, result, b);
        }



        // Functions below here are intended to form the public interface of the library ------------------

        // Setup static instance of Logger and add default destinations
        static void SetupLogging(int debugLevel = 0)
        {
            Logger::instance().AddStdoutDestination({ Level::Info, Level::Warning, Level::Debug });
            Logger::instance().AddStderrDestination({ Level::Error });
            Logger::instance().SetDebugLevel(debugLevel);
        }

        // Optional shutdown function, can be called when all logging is done, 
        // or objects will be freed when program exits
        static void ShutdownLogging()
        {
            Logger::instance().Shutdown();
        }

        static void SetDebugLevel(int debugLevel)
        {
            Logger::instance().SetDebugLevel(debugLevel);
        }

        static int GetDebugLevel()
        {
            return Logger::instance().GetDebugLevel();
        }

        // Creates file destination for all levels
        // Could enable routing specific levels to different files if needed, but why?
        static void AddFileDestination(const std::string &filePath)
        {
            Logger::instance().AddFileDestination(filePath);
        }

        // Info message
        static void Info(
            const std::string &doing,
            const std::string &result,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Info, doing, result, data);
        }

        static void Info(
            const std::string &info,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Info, info, "", data);
        }

        // Info message with info blob

        static void Info(
            const std::string &info,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Info, info, "", blob, data);
        }

        static void Info(
            const std::string &doing,
            const std::string &result,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Info, doing, result, blob, data);
        }

        static void Warning(
            const std::string &doing,
            const std::string &result,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Warning, doing, result, data);
        }

        static void Warning(
            const std::string &doing,
            const std::string &result,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Warning, doing, result, blob, data);
        }

        static void Error(
            const std::string &doing,
            const std::string &result,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Error, doing, result, data);
        }

        static void Error(
            const std::string &doing,
            const std::string &result,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            Log(Level::Error, doing, result, blob, data);
        }

        static void Debug(
            int debugLevel,
            const std::string &doing,
            const std::string &result,
            const std::initializer_list<I> &data = {})
        {
            Logger::instance().Debug(debugLevel, doing, result, data);
        }

        static void Debug(
            int debugLevel,
            const std::string &debug,
            const std::initializer_list<I> &data = {})
        {
            Logger::instance().Debug(debugLevel, debug, "", data);
        }

        static void Debug(
            int debugLevel,
            const std::string &debug,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            // Merge blob and data
            InfoBlob b = blob;
            b.insert(b.end(), data);
            Logger::instance().Debug(debugLevel, debug, "", b);
        }

        static void Debug(
            int debugLevel,
            const std::string &doing,
            const std::string &result,
            const InfoBlob &blob,
            const std::initializer_list<I> &data = {})
        {
            // Merge blob and data
            InfoBlob b = blob;
            b.insert(b.end(), data);
            Logger::instance().Debug(debugLevel, doing, result, b);
        }
	}
}



#endif