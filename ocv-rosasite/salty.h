#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "inputHandler.hpp"

struct userDataSalty
{
    cv::Mat src;
    cv::Mat result;
};

std::vector<cv::Mat> saltEffect(const InputHandler &inputHandler);

cv::Mat saltEffect(cv::Mat src);

void salt(int amount, userDataSalty *userdata);

void saltTrackbarCallback(int amount, void* userdata);
