#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "inputHandler.hpp"

struct UserDataForResizeAndRotate
{
    cv::Mat src;
    cv::Mat result;
    int angle = 0;
    int scale = 50;
};

cv::Mat resizeAndRotate(cv::Mat image);
std::vector<cv::Mat> resizeAndRotate(const InputHandler &inputHandler);
cv::Mat getRotatedAndResizedImage(cv::Mat image, int angle, int scale);
void resizeAndRotateTrackbarCallback(int pos, void* userdata);
