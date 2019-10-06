#pragma once
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include "inputHandler.hpp"

struct UserDataForDetectCorners
{
    cv::Mat src;
    cv::Mat result;
    int threshold;
};

cv::Mat harrisCornerDetection(UserDataForDetectCorners *userData);
void detectCornersTrackbarCallback(int threshold, void* userdata);
cv::Mat detectCorners(cv::Mat image);
std::vector<cv::Mat> detectCorners(const InputHandler &inputHandler);
