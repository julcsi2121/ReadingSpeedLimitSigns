#include "gtest/gtest.h"
#include "detectEdges.h"


TEST(DetectEdgesTests, CannyHandlesEmptyMat)
{
    cv::Mat src;

    EXPECT_ANY_THROW(detectEdges(src));
}

TEST(DetectEdgesTests, CannyHandlesSimpleInput)
{
    cv::Vec3b pixelA = { 255, 0, 0 };
    cv::Vec3b pixelB = { 0, 255, 0 };
    cv::Mat src(100, 100, CV_8UC3, pixelA);
    cv::Mat result;
    userDataDetectEdges userdata = { src, result, 100, 200 };

    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < src.cols; j++) {
            src.at<cv::Vec3b>(i, j) = pixelB;
        }
    }

    cannyEdgeDetection(&userdata);
    
    EXPECT_EQ(cv::countNonZero(userdata.result), 100);
}

TEST(DetectEdgesTests, CannyHandlesNegativeThreshold)
{
    cv::Vec3b pixelA = { 255, 0, 0 };
    cv::Vec3b pixelB = { 0, 255, 0 };
    cv::Mat src(100, 100, CV_8UC3, pixelA);
    cv::Mat result;
    userDataDetectEdges userdata = { src, result, 300, -50 };

    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < src.cols; j++) {
            src.at<cv::Vec3b>(i, j) = pixelB;
        }
    }

    cannyEdgeDetection(&userdata);

    EXPECT_EQ(cv::countNonZero(userdata.result), 100);
}

TEST(DetectEdgesTests, CannyHandles1C)
{
    cv::Mat src(100, 100, CV_8UC1, 30);
    cv::Mat result;
    userDataDetectEdges userdata = { src, result, 100, 200 };

    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < src.cols; j++) {
            src.at<cv::uint8_t>(i, j) = 220;
        }
    }

    cannyEdgeDetection(&userdata);

    EXPECT_EQ(cv::countNonZero(userdata.result), 100);
}
