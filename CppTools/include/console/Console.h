#ifndef __CONSOLE__H__
#define __CONSOLE__H__ 1


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdexcept>
#include <sstream>

/**
class Console
{
    public:

        Console();

        ~Console();

        const static void printTable(std::vector<std::string> labels, std::vector<std::vector<std::string>> tableMatrix);

        static int executeCommandBlock(const char* command, std::string& stdOut);
        bool executeCommandAsync(const char* command);

        bool hasCommandFinished();
        int commandResponse(std::string& stdOut);

    private:

        std::mutex mtx;
        std::condition_variable cv;
        std::string stdOut;
        int status;
        bool commandInProgress;

};
*/

/**
 * @brief The Console class provides utility methods to execute shell commands and capture their output.
 *
 * This class allows synchronous and asynchronous execution of shell commands, along with capturing
 * the standard output and exit status of the executed command. It uses multi-threading for asynchronous
 * execution and synchronization with a condition variable.
 */
class Console {
public:
    /**
     * @brief Constructor for the Console class.
     *
     * Initializes the Console object. The constructor does not require any parameters.
     * It will initialize the internal variables to their default values.
     */
    Console();

    /**
     * @brief Destructor for the Console class.
     *
     * The destructor is responsible for cleaning up the Console object. It does not
     * have any specific actions in this class.
     */
    ~Console();

    /**
     * @brief Print a table with labels and data in a well-formatted manner.
     *
     * This static method takes two vectors, labels and tableMatrix, and prints the data
     * as a table in the console. The labels vector contains the header of the table,
     * while the tableMatrix is a 2D vector containing the data to be printed.
     *
     * @param labels The vector containing the labels for each column of the table.
     * @param tableMatrix The 2D vector containing the data to be printed in the table.
     */
    const static void printTable(std::vector<std::string> labels, std::vector<std::vector<std::string>> tableMatrix);

    /**
     * @brief Execute a shell command and capture the standard output synchronously.
     *
     * This static method executes a shell command and captures the standard output in the
     * provided stdOut string. The command is executed synchronously, and the method will
     * wait for the command to finish before returning.
     *
     * @param command The shell command to be executed.
     * @param stdOut A string to store the standard output of the executed command.
     * @return The exit status of the executed command.
     */
    static int executeCommandBlock(const char* command, std::string& stdOut);

    /**
     * @brief Execute a shell command asynchronously.
     *
     * This method launches a new thread to execute the given shell command. The method will
     * return immediately after launching the thread. The result of the command execution
     * can be checked using the hasCommandFinished and commandResponse methods.
     *
     * @param command The shell command to be executed.
     * @return True if the thread was successfully launched, false if a command is already in progress.
     */
    bool executeCommandAsync(const char* command);

    /**
     * @brief Check if the asynchronous command execution has finished.
     *
     * This method checks if the asynchronous command execution has finished. It returns true if
     * the command has finished executing and false if it is still in progress.
     *
     * @return True if the command has finished executing, false otherwise.
     */
    bool hasCommandFinished();

    /**
     * @brief Get the standard output and exit status of the last executed command.
     *
     * This method returns the standard output and exit status of the last executed command.
     * If no command has been executed, it will return -1 as the exit status and an empty 
     * string as the standard output. The user should call this method after ensuring that
     * the asynchronous command execution has finished by using the hasCommandFinished method.
     * If the user has already launched a new command with executeCommandAsync before checking
     * if the previous command has finished, the method will return the response of the last
     * executed command, which may lead to an unpredictable result. It is the user's
     * responsibility to ensure the proper sequence of calls for correct behavior.
     *
     * @param stdOutResp A string to store the standard output of the executed command.
     * @return The exit status of the last executed command.
     */
    int commandResponse(std::string& stdOutResp);

private:
    std::mutex mtx;                     ///< Mutex to protect access to shared resources.
    std::condition_variable cv;        ///< Condition variable to synchronize threads.
    std::string stdOut;                ///< Standard output of the last executed command.
    int status;                         ///< Exit status of the last executed command.
    bool commandInProgress;    ///< Flag indicating if a command is currently in progress.
};


#endif // __CONSOLE__H__
