#pragma once
#include <vector>
#include "reduceColor.h"
#include "detectEdges.h"
#include "inputHandler.hpp"

cv::Mat cartoonEffect(cv::Mat image);
std::vector<cv::Mat> cartoonEffect(const InputHandler &inputHandler);
