#include "setupMode.hpp"

#include <iostream>
#include <sqlite3.h>
#include "readSpeedLimitSign.h"

int callbackParamDB(void* data, int argc, char** argv, char** colName)
{
    return 0;
}

void initDB()
{
    sqlite3 *db = nullptr;
    int err = sqlite3_open("database.db", &db);
    if (err != SQLITE_OK)
        throw std::runtime_error("Can not read or create the parameter database!");
    
    std::string createTable = R"(
    CREATE TABLE IF NOT EXISTS Parameters (
    ID          INTEGER PRIMARY KEY AUTOINCREMENT,
    DISTANCE    INT     NOT NULL,
    CANNYEDGE   INT     NOT NULL,
    CENTER      INT     NOT NULL,
    MIN_RAD     INT     NOT NULL,
    MAX_RAD     INT     NOT NULL,
    KERNEL      INT     NOT NULL,
    BORDER      INT     NOT NULL,
    NAME        TEXT    NOT NULL
    );)";
    
    char* errorMessage;
    err = sqlite3_exec(db, createTable.c_str(), callbackParamDB, nullptr, &errorMessage);
    if (err != SQLITE_OK)
        throw std::runtime_error(errorMessage);
}

void insertParam(int distance, int cannyEdge, int center, int minRad, int maxRad, int kernel, int border, std::string name)
{
    sqlite3 *db = nullptr;
    sqlite3_stmt* sqlStatement;
    
    int err = sqlite3_open("database.db", &db);
    if (err != SQLITE_OK)
        throw std::runtime_error("Can not read or create the parameter database!");
    
    std::string insert = R"(
    INSERT INTO Parameters (DISTANCE, CANNYEDGE, CENTER, MIN_RAD, MAX_RAD, KERNEL, BORDER, NAME)
    VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8)
    ;)";
    
    err = sqlite3_prepare_v2(db, insert.c_str(), -1, &sqlStatement, nullptr);
    
    sqlite3_bind_int(sqlStatement, 1, distance);
    sqlite3_bind_int(sqlStatement, 2, cannyEdge);
    sqlite3_bind_int(sqlStatement, 3, center);
    sqlite3_bind_int(sqlStatement, 4, minRad);
    sqlite3_bind_int(sqlStatement, 5, maxRad);
    sqlite3_bind_int(sqlStatement, 6, kernel);
    sqlite3_bind_int(sqlStatement, 7, border);
    sqlite3_bind_text(sqlStatement, 8, name.c_str(), -1, nullptr);
    
    err = sqlite3_step(sqlStatement);
    if (err != SQLITE_DONE)
        throw std::runtime_error("Can not bind the given values!");
}

void distanceCallback(int distance, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->maximumDistance = distance * 4;
}

void cannyEdgeCallback(int cannyEdge, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->cannyEdgeUpperTreshold = 100 + (cannyEdge * 2);
}

void centerCallback(int center, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->centerDetectionTreshold = center * 2;
}

void minRadCallback(int minRad, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->minRad = minRad * 2;
}

void maxRadCallback(int maxRad, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->maxRad = maxRad * 2;
}

void kernelCallback(int kernel, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->kernelSize = 3 + (kernel * 2);
}

void borderCallback(int border, void* userData)
{
    userDataForSpeedLimitReading* data = (userDataForSpeedLimitReading*) userData;
    data->border = border * 5;
}

void setup(std::string preset)
{
    initDB();
    userDataForSpeedLimitReading param;
    FilterSignLimit filter(2);
    cv::VideoCapture cap(0);
    std::string paramWin = "Settings";
    cv::namedWindow(paramWin, cv::WINDOW_NORMAL);
    cv::resizeWindow(paramWin, 1000, 40);
    cv::moveWindow(paramWin, 0, 650);
    
    cv::createTrackbar("Distance",      paramWin, &param.maximumDistance,    50, distanceCallback,  &param);
    cv::createTrackbar("CannyEdge",     paramWin, &param.cannyEdgeUpperTreshold,  50, cannyEdgeCallback, &param);
    cv::createTrackbar("Center",        paramWin, &param.centerDetectionTreshold,      50, centerCallback,    &param);
    cv::createTrackbar("Radius (min)",  paramWin, &param.minRad,      50, minRadCallback,    &param);
    cv::createTrackbar("Radius (max)",  paramWin, &param.maxRad,      50, maxRadCallback,    &param);
    cv::createTrackbar("Kernel Size",   paramWin, &param.kernelSize,      11, kernelCallback,    &param);
    cv::createTrackbar("Border Size",   paramWin, &param.border,      20, borderCallback,    &param);
    
    cv::setTrackbarPos("Distance",      paramWin, param.maximumDistance / 4.0);
    cv::setTrackbarPos("CannyEdge",     paramWin, (param.cannyEdgeUpperTreshold - 100) / 2.0);
    cv::setTrackbarPos("Center",        paramWin, param.centerDetectionTreshold / 2.0);
    cv::setTrackbarPos("Radius (min)",  paramWin, param.minRad / 2.0);
    cv::setTrackbarPos("Radius (max)",  paramWin, param.maxRad / 2.0);
    cv::setTrackbarPos("Kernel Size",   paramWin, (param.kernelSize - 3) / 2.0);
    cv::setTrackbarPos("Border Size",   paramWin, param.border / 5.0);
    
    while (1) {
        cv::Mat frame;
        cap >> frame;
        int width = frame.cols * (400.0 / frame.rows);
        cv::resize(frame, frame, cv::Size(width, 400));
        readSpeedLimitSign(frame, param, filter);
        cv::imshow("Preview", frame);
        if (cv::waitKey(30) >= 0)
            break;
    }
    
    insertParam(param.maximumDistance, param.cannyEdgeUpperTreshold, param.centerDetectionTreshold, param.minRad, param.maxRad, param.kernelSize, param.border, preset);
    cv::destroyAllWindows();
}
