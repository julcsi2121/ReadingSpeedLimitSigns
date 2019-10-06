#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "inputHandler.hpp"

cv::Mat wave(cv::Mat image);
std::vector<cv::Mat> wave(const InputHandler &inputHandler);

