#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "inputHandler.hpp"

cv::Mat sharpen(cv::Mat src);
std::vector<cv::Mat> sharpen(const InputHandler &inputHandler);
