#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "inputHandler.hpp"

struct arithmeticUserData
{
    cv::Mat image;
    int scalar;
    cv::Mat result;
};

cv::Mat addMats(cv::Mat image1, cv::Mat image2);

std::vector<cv::Mat> addMats(const InputHandler &inputHandler);

cv::Mat subtractMats(cv::Mat image1, cv::Mat image2);

std::vector<cv::Mat> subtractMats(const InputHandler &inputHandler);

cv::Mat multiplyMats(cv::Mat image1, cv::Mat image2);

std::vector<cv::Mat> multiplyMats(const InputHandler &inputHandler);

cv::Mat multiplyWithScalar(cv::Mat image1, int scalar);

std::vector<cv::Mat> multiplyWithScalar(const InputHandler &inputHandler);

void trackBarCallback(int scalar, void *userdata);

cv::Mat scalar(cv::Mat image);
