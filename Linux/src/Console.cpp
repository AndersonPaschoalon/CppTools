#include "Console.h"

Console::Console()
{
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

/*
int Console::executeCommand(const char *command, int mode, std::string &stdOut)
{
        std::lock_guard<std::mutex> lock(mutex_);

        if (mode == 0) {
            FILE* pipe = popen(command, "r");
            if (!pipe) 
            {
                return -1;
            }

            char buffer[128];
            while (fgets(buffer, 128, pipe) != nullptr) {
                stdOut += buffer;
            }

            return_code_ = pclose(pipe);
            finished_ = true;

            return return_code_;
        }
        else if (mode == 1) 
        {
            if (!finished_) 
            {
                return -1;
            }

            finished_ = false;

            std::thread([this, command]() {
                FILE* pipe = popen(command, "r");
                if (!pipe) {
                    return_code_ = -1;
                    finished_ = true;
                    return;
                }

                char buffer[128];
                while (fgets(buffer, 128, pipe) != nullptr) {
                    std::lock_guard<std::mutex> lock(mutex_);
                    stdOut += buffer;
                }

                return_code_ = pclose(pipe);
                finished_ = true;

                std::unique_lock<std::mutex> lock(cv_mutex_);
                finished_cv_.notify_one();
            }).detach();

            return 0;
        }

        return -1;
}


bool Console::commandFinished(std::string &stdOut, int &retCode)
{
        std::lock_guard<std::mutex> lock(mutex_);

        if (!finished_) {
            return false;
        }

        stdOut = stdOut_;
        retCode = return_code_;

        finished_ = false;

        return true;
}
**/