#pragma once
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "inputHandler.hpp"

std::vector<cv::Mat> detectText(cv::Mat image, std::string path = _EAST_MODEL_PATH);
cv::Mat rotatedRectToMat(cv::RotatedRect rect, cv::Mat image);
std::vector<std::vector<cv::Mat>> detectText(const InputHandler &inputHandler);