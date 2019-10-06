#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "inputHandler.hpp"

struct userDataDetectEdges
{
    cv::Mat src;
    cv::Mat result;
    int tresholdMin;
    int tresholdMax;
};

cv::Mat detectEdges(cv::Mat image);
void trackbarCallbackMin(int min, void *userdata);
void trackbarCallbackMax(int min, void *userdata);
void cannyEdgeDetection(userDataDetectEdges *userdata);
std::vector<cv::Mat> detectEdges(const InputHandler &inputHandler);
