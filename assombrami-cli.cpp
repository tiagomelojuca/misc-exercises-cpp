#include <iostream>
#include <cstdlib>
#include <cstring>
#include <filesystem>

// NOTE: Using filesystem, requires --std=c++17
int main(int argc, char **argv)
{
    int projectNumber = atoi(argv[1]);
    char projectNumberAsString[3];
    char folderName[14] = "assombrami-";
    char audioPath[20];
    char videoPath[20];

    if(projectNumber == 0 || projectNumber < 0 || projectNumber > 999) {
        std::cout << "ERROR: Please inform a valid integer (1 to 999)" << std::endl;
        return 1;
    }

    if(projectNumber < 10) {
        strcpy(projectNumberAsString, "00");
        strcat(projectNumberAsString, argv[1]);
    }

    if(projectNumber > 9 && projectNumber < 100) {
        strcpy(projectNumberAsString, "0");
        strcat(projectNumberAsString, argv[1]);
    }

    if(projectNumber > 99) {
        strcpy(projectNumberAsString, argv[1]);
    }

    strcat(folderName, projectNumberAsString);

    bool folderAlreadyExists = std::filesystem::exists(folderName);

    if(folderAlreadyExists) {
        std::cout << "ERROR: The informed project number already exists" << std::endl;
        return 1;
    }

    strcpy(audioPath, folderName);
    strcat(audioPath, "/audio");
    strcpy(videoPath, folderName);
    strcat(videoPath, "/video");

    std::filesystem::create_directory(folderName);
    std::filesystem::create_directory(audioPath);
    std::filesystem::create_directory(videoPath);

    char successMessage[55] = "Your project was successfully created at ";
    strcat(successMessage, folderName);

    std::cout << successMessage << std::endl;

    return 0;
}
