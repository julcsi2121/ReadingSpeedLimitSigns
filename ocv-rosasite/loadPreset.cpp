#include "loadPreset.hpp"
#include <iostream>
#include <sqlite3.h>
#include <opencv2/opencv.hpp>
#include "readSpeedLimitSign.h"

int callbackLoadPreset(void* data, int argc, char** argv, char** colName)
{
    userDataForSpeedLimitReading* preset = (userDataForSpeedLimitReading*)data;

    preset->maximumDistance = std::atoi(argv[1]);
    preset->cannyEdgeUpperTreshold = std::atoi(argv[2]);
    preset->centerDetectionTreshold = std::atoi(argv[3]);
    preset->minRad = std::atoi(argv[4]);
    preset->maxRad = std::atoi(argv[5]);
    preset->kernelSize = std::atoi(argv[6]);
    preset->border = std::atoi(argv[7]);
    preset->name = argv[8];

    return 0;
}

void loadPreset(std::string name)
{
    sqlite3 *db = nullptr;
    int err = sqlite3_open("database.db", &db);
    if (err != SQLITE_OK)
        throw std::runtime_error("Can load the parameter database!");
    
    char* errorMessage;
    userDataForSpeedLimitReading preset;
    FilterSignLimit filter(2);
    
    std::string queryParams = "SELECT * FROM Parameters WHERE NAME='" + name + "' AND ID = (SELECT MAX(ID) FROM Parameters WHERE NAME='" + name + "');";
    err = sqlite3_exec(db, queryParams.c_str(), callbackLoadPreset, (void*)&preset, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
    
    if (preset.name == "default")
        std::cerr << "Preset did not exist. Default values loaded." << std::endl;
    
    cv::VideoCapture cap(0);
    cv::Mat frame;
    while (1) {
        cap >> frame;
        readSpeedLimitSign(frame, preset, filter);
        cv::imshow("Preview", frame);
        if (cv::waitKey(30) >= 0)
            break;
    }
}
