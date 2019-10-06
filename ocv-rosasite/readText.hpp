#pragma once

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "inputHandler.hpp"

std::string readText(cv::Mat image, int border = 20, bool isWordToRecognize = true);
void readText(const InputHandler &inputHandler);
