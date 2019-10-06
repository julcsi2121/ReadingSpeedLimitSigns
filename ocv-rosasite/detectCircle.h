#pragma once
#include <opencv2/opencv.hpp>
#include "shellSort.h"
#include <vector>
#include "inputHandler.hpp"

struct userDataForDetectCircle
{
    cv::Mat src;
    std::vector<cv::Vec3i> circles;
    int maximumDistance = 30;
    int cannyEdgeUpperTreshold = 150;
    int centerDetectionTreshold = 100;
};

std::vector<cv::Vec3i> detectCircle(cv::Mat image);
std::vector<std::vector<cv::Vec3i>> detectCircle(const InputHandler &inputHandler);
std::vector<cv::Vec3i> circleDetection(cv::Mat image, int minimumDistance, int cannyEdgeUpperTreshold, int centerDetectionTreshold, int minRad = 0, int maxRad = 100);