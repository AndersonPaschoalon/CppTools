#include "OSUtils.h"


bool OSUtils::fileExists(const char *fileName)
{
    FILE *file;
    if ((file = fopen(fileName, "r")))
    {
        fclose(file);
        return true;
    }
    return false;
}

bool OSUtils::deleteFileIfExists(const char* filename)
{
    // Check if the file exists
    std::ifstream file(filename);
    bool exists = file.good();
    file.close();

    // If the file exists, delete it
    if (exists)
    {
        if (std::remove(filename) != 0)
        {
            // Error deleting the file
            return false;
        }
    }

    // Return true if the file was deleted or if it did not exist
    return true;
}


bool OSUtils::appendToFile(std::string fileName, std::string content)
{
    std::ofstream outFile(fileName, std::ios_base::app);
    if (!outFile) 
    {
        // If the file doesn't exist, create a new one
        outFile.open(fileName);
        if (!outFile) 
        {
            std::cerr << "Error creating file: " << fileName << std::endl;
            return false;
        }
    }

    outFile << content;
    outFile.close();
    return true;
}

std::string OSUtils::getFileName(const char *fullPath, bool removeExtension)
{
    std::string fileName(fullPath);
    size_t lastSlash = fileName.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
        fileName = fileName.substr(lastSlash + 1);
    }

    if (removeExtension) 
    {
        size_t lastDot = fileName.find_last_of(".");
        if (lastDot != std::string::npos) {
            fileName = fileName.substr(0, lastDot);
        }
    }

    return fileName;
}


