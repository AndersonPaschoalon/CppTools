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
