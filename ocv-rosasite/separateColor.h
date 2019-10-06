#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "inputHandler.hpp"

std::vector<cv::Mat> separateColor(const InputHandler &inputHandler);
std::vector<cv::Mat> separateColor(cv::Mat images);
