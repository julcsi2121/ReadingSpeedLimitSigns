#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "inputHandler.hpp"

struct TrackbarData {
    cv::Mat* image;
    cv::Mat result;
    int brigthness = 50;
    int contrast = 50;
};

cv::Mat histogram(cv::Mat image, bool editMode = true);
std::vector<cv::Mat> histogram(const InputHandler &inputHandler);

void brigthnessCallback(int value, void* userData);
void contrastCallback(int value, void* userData);
