#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "inputHandler.hpp"

struct userData
{
    cv::Mat* src;
    cv::Mat* result;
    int divideWith;
};

cv::Mat reduceColor(cv::Mat image);
std::vector<cv::Mat> reduceColor(const InputHandler &inputHandler);

cv::Mat calculateLookUpTable(int divideWith);
cv::Mat getColorReducedImage(cv::Mat *image, cv::Mat *lookUpTable);

void trackbarCallback(int divideWith, void* userdata);
