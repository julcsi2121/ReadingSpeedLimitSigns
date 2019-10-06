#include "gtest/gtest.h"
#include "separateColor.h"

TEST(SeparateColorTest, BlueChannelIsOriginalGreenAndRedZero)
{
    cv::Mat whiteImage(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));

    std::vector<cv::Mat> imagesSeparatedByColor = separateColor(whiteImage);

    cv::Mat blueImage = imagesSeparatedByColor[0];

    cv::Vec3b pixelToCheck = blueImage.at<cv::Vec3b>(50, 50);

    EXPECT_EQ(pixelToCheck[0], 255);

    EXPECT_EQ(pixelToCheck[1], 0);

    EXPECT_EQ(pixelToCheck[2], 0);
}

TEST(SeparateColorTest, GreenChannelIsOriginalBlueAndRedZero)
{
    cv::Mat whiteImage(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));

    std::vector<cv::Mat> imagesSeparatedByColor = separateColor(whiteImage);

    cv::Mat greenImage = imagesSeparatedByColor[1];

    cv::Vec3b pixelToCheck = greenImage.at<cv::Vec3b>(20, 15);

    EXPECT_EQ(pixelToCheck[0], 0);

    EXPECT_EQ(pixelToCheck[1], 255);

    EXPECT_EQ(pixelToCheck[2], 0);
}

TEST(SeparateColorTest, RedChannelIsOriginalBlueAndGreenZero)
{
    cv::Mat whiteImage(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));

    std::vector<cv::Mat> imagesSeparatedByColor = separateColor(whiteImage);

    cv::Mat redImage = imagesSeparatedByColor[2];

    cv::Vec3b pixelToCheck = redImage.at<cv::Vec3b>(90, 20);

    EXPECT_EQ(pixelToCheck[0], 0);

    EXPECT_EQ(pixelToCheck[1], 0);

    EXPECT_EQ(pixelToCheck[2], 255);
}
