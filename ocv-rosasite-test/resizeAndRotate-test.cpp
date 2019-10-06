#include "gtest/gtest.h"
#include "resizeAndRotate.h"

static void EXPECT_EQ_MAT(cv::Mat m1, cv::Mat m2)
{
    EXPECT_EQ(m1.size, m2.size);
    EXPECT_EQ(m1.type(), m2.type());

    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            EXPECT_EQ(m1.at<cv::Vec3b>(i, j), m2.at<cv::Vec3b>(i, j));
        }
    }
}

TEST(ResizeAndRotateTest, TestWith90Degree)
{
    cv::Mat testPicture(10, 10, CV_8UC3);

    for (int i = 0; i < testPicture.rows; ++i) {
        for (int j = 0; j < testPicture.cols; ++j) {
            if (i < 2 || i >= 8) {
                testPicture.at<cv::Vec3b>(i, j) = {255, 0, 0};
            }
            else {
                testPicture.at<cv::Vec3b>(i, j) = {0, 255, 0};
            }
        }
    }

    cv::Mat result = getRotatedAndResizedImage(testPicture, 90, 50);

    cv::Vec3b pixelTocheck = result.at<cv::Vec3b>(9, 5);

    EXPECT_EQ(pixelTocheck[0], 0);
    EXPECT_EQ(pixelTocheck[1], 255);
    EXPECT_EQ(pixelTocheck[2], 0);
}

TEST(ResizeAndRotateTest, TestWith180Degree)
{
    cv::Mat testPicture(9, 9, CV_8UC3);

    for (int i = 0; i < testPicture.rows; ++i) {
        for (int j = 0; j < testPicture.cols; ++j) {
            if (i < 2 || i > 6) {
                testPicture.at<cv::Vec3b>(i, j) = {255, 0, 0};
            }
            else {
                testPicture.at<cv::Vec3b>(i, j) = {0, 255, 0};
            }
        }
    }

    cv::Mat result = getRotatedAndResizedImage(testPicture, 180, 50);

    EXPECT_EQ_MAT(result, testPicture);
}

TEST(ResizeAndRotateTest, TestWithSmallerSize)
{
    cv::Mat testPicture(10, 10, CV_8UC3);

    for (int i = 0; i < testPicture.rows; ++i) {
        for (int j = 0; j < testPicture.cols; ++j) {
            if (i < 2 || i >= 8) {
                testPicture.at<cv::Vec3b>(i, j) = {255, 0, 0};
            }
            else {
                testPicture.at<cv::Vec3b>(i, j) = {0, 255, 0};
            }
        }
    }

    cv::Mat result = getRotatedAndResizedImage(testPicture, 0, 30);

    cv::Vec3b pixelTocheck = result.at<cv::Vec3b>(0, 5);

    EXPECT_EQ(pixelTocheck[0], 0);
    EXPECT_EQ(pixelTocheck[1], 0);
    EXPECT_EQ(pixelTocheck[2], 0);
}
