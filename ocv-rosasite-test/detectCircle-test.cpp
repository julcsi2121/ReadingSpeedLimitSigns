#include "gtest/gtest.h"
#include "detectCircle.h"

TEST(DetectCircleTest, TestWithZeroCircle)
{
    cv::Mat image(10, 10, CV_8UC3, cv::Scalar(0, 0, 255));

    std::vector<cv::Vec3i> detectedCircles = circleDetection(image, 5, 150, 100);

    int numberOfDetectCircles = detectedCircles.size();

    EXPECT_EQ(numberOfDetectCircles, 0);
}

TEST(DetectCircleTest, TestWithOneCircle)
{
    cv::Mat image(90, 90, CV_8UC3, cv::Scalar(255, 255, 255));
    int x = 45;
    int y = 45;
    int radius = 40;

    cv::circle(image, {x, y}, radius, cv::Scalar(0, 0, 0), -1);

    std::vector<cv::Vec3i> detectedCircles = circleDetection(image, 1, 150, 100);

    int numberOfDetectCircles = detectedCircles.size();

    ASSERT_EQ(numberOfDetectCircles, 1);
    EXPECT_EQ(detectedCircles[0][0], x);
    EXPECT_EQ(detectedCircles[0][1], y);
    EXPECT_NEAR(detectedCircles[0][2], radius, 1);
}