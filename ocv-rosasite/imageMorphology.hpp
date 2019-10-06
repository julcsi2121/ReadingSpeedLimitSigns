#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include "inputHandler.hpp"

cv::Mat dilate(cv::Mat image);
std::vector<cv::Mat> dilate(const InputHandler &inputHandler);

cv::Mat erode(cv::Mat image);
std::vector<cv::Mat> erode(const InputHandler &inputHandler);

cv::Mat open(cv::Mat image);
std::vector<cv::Mat> open(const InputHandler &inputHandler);

cv::Mat close(cv::Mat image);
std::vector<cv::Mat> close(const InputHandler &inputHandler);

