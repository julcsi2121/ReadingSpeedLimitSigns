#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "inputHandler.hpp"

cv::Mat decoloring(cv::Mat image);
std::vector<cv::Mat> decoloring(const InputHandler &inputHandler);
