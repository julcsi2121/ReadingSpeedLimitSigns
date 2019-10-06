#include "gtest/gtest.h"
#include "detectText.h"
#include <filesystem>

TEST(DetectTextTests, TestEmptyInput) {
    cv::Mat src;
    std::vector<cv::Mat> result = detectText(src);
    EXPECT_EQ(result.size(), 0);
}

TEST(DetectTextTests, TestNonTextInput) {
    cv::Mat src = cv::Mat::zeros(40, 40, CV_8UC3);
    cv::circle(src, cv::Point(20, 20), 7, cv::Scalar(255, 255, 255), 1);
    std::vector<cv::Mat> result = detectText(src);
    EXPECT_EQ(result.size(), 0);
}

TEST(DetectTextTests, TestTextInput) {
    cv::Mat src = cv::Mat::zeros(80, 80, CV_8UC3);
    cv::putText(src, "ab", cv::Point(10, 40), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 2, cv::Scalar(255, 255, 255), 2);
    std::vector<cv::Mat> result = detectText(src);

    EXPECT_EQ(result.size(), 1);
}