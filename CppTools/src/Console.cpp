#include "Console.h"

Console::Console()
{
    this->commandInProgress = false;
    this->stdOut.clear();
    this->status = -1;
}

Console::~Console()
{
}

const void Console::printTable(std::vector<std::string> labels, std::vector<std::vector<std::string>> tableMatrix)
{
    // Determine the maximum width of each column
    std::vector<int> column_widths(labels.size(), 0);
    for (int i = 0; i < labels.size(); i++) {
        column_widths[i] = labels[i].length();
        for (int j = 0; j < tableMatrix.size(); j++) {
            if (tableMatrix[j][i].length() > column_widths[i]) 
            {
                column_widths[i] = tableMatrix[j][i].length();
            }
        }
    }

    // Print the column labels
    for (int i = 0; i < labels.size(); i++) 
    {
        std::cout << std::setw(column_widths[i]) << std::left << labels[i] << " ";
    }
    std::cout << std::endl;

    // Print the separator line
    for (int i = 0; i < labels.size(); i++) 
    {
        std::cout << std::setw(column_widths[i]) << std::setfill('-') << "" << " ";
    }
    std::cout << std::setfill(' ') << std::endl;

    // Print the table data
    for (int i = 0; i < tableMatrix.size(); i++) 
    {
        for (int j = 0; j < labels.size(); j++) {
            std::cout << std::setw(column_widths[j]) << std::left << tableMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Console::executeCommandBlock(const char *command, std::string &stdOut)
{
    // NEED TEST!!!!
    std::string cmdOutput;
    char buffer[128];

    // Open a pipe to the command and read its output
    FILE* pipe = popen(command, "r");
    if (!pipe) 
    {
        stdOut = "Error executing the command.";
        return -1;
    }

    // Read the command output into the buffer
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) 
    {
        cmdOutput += buffer;
    }

    // Close the pipe
    int status = pclose(pipe);

    // Set the output string
    stdOut = cmdOutput;

    // Return the command status
    return status;
}

bool Console::executeCommandAsync(const char *command)
{
        std::unique_lock<std::mutex> lock(this->mtx);
        if (this->commandInProgress) 
        {
            return false; // Command already running
        }

        this->commandInProgress = true;
        //this->stdOut.clear();
        // this->status = -1;

        // Launch a new thread to execute the command
        std::thread t([this, command]() 
        {
            try 
            {
                // Open a pipe to the command and read its output
                std::string cmdOutput;
                char buffer[8192];
                FILE* pipe = popen(command, "r");
                if (!pipe) 
                {
                    throw std::runtime_error("Error executing the command.");
                }

                while (fgets(buffer, sizeof(buffer), pipe) != NULL) 
                {
                    cmdOutput += buffer;
                }

                int exitCode = pclose(pipe);

                std::lock_guard<std::mutex> lock(this->mtx);
                this->stdOut = cmdOutput;
                this->status = WEXITSTATUS(exitCode);
                this->commandInProgress = false;
                cv.notify_all(); // Notify that the command has finished
            } catch (const std::exception& ex) 
            {
                std::lock_guard<std::mutex> lock(this->mtx);
                this->stdOut = "Error: ";
                this->stdOut += ex.what();
                this->status = -1;
                this->commandInProgress = false;
                cv.notify_all(); // Notify that the command has finished
            }
        });

        t.detach();
        return true;
}


bool Console::hasCommandFinished()
{
    std::lock_guard<std::mutex> lock(this->mtx);
    return !this->commandInProgress;
}

int Console::commandResponse(std::string &stdOutResp)
{
    std::lock_guard<std::mutex> lock(this->mtx);
    stdOutResp = this->stdOut;
    return this->status;
}
