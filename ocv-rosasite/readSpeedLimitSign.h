#pragma once

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "detectCircle.h"
#include "detectText.h"
#include "readText.hpp"
#include "separateColor.h"
#include "inputHandler.hpp"
#include "filterSignLimit.h"

struct userDataForSpeedLimitReading
{
    int maximumDistance = 5;
    int cannyEdgeUpperTreshold = 150;
    int centerDetectionTreshold = 100;
    int kernelSize = 3;
    int minRad = 0;
    int maxRad = 100;
    int border = 20;
    std::string name;
};

int readSpeedLimitSign (cv::Mat image, userDataForSpeedLimitReading userData, FilterSignLimit &filter);
std::vector<int> readSpeedLimitSign(const InputHandler &inputHandler);