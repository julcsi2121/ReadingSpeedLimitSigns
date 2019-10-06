#include <gtest/gtest.h>
#include "histogram.hpp"

TEST(Histogram, testIfInputHistogramIsBlueAtGivenPoint)
{
    cv::Mat img(10, 10, CV_8UC3, cv::Scalar(128, 0, 0));
    cv::Mat result;
    result = histogram(img);
    
    std::vector<cv::Mat> channels;
    cv::split(result, channels);
    
    int count = cv::countNonZero(channels.at(0));
    
    EXPECT_GT(count, 0);
}

TEST(Histogram, testIfInputHistogramIsGreenAtGivenPoint)
{
    cv::Mat img(10, 10, CV_8UC3, cv::Scalar(0, 128, 0));
    cv::Mat result;
    result = histogram(img);
    
    std::vector<cv::Mat> channels;
    cv::split(result, channels);
    
    int count = cv::countNonZero(channels.at(1));
    
    EXPECT_GT(count, 0);
}

TEST(Histogram, testIfInputHistogramIsRedAtGivenPoint)
{
    cv::Mat img(10, 10, CV_8UC3, cv::Scalar(0, 0, 128));
    cv::Mat result;
    result = histogram(img);
    
    std::vector<cv::Mat> channels;
    cv::split(result, channels);
    
    int count = cv::countNonZero(channels.at(2));
    
    EXPECT_GT(count, 0);
}

TEST(Histogram, testIfErrorOneChanelImage)
{
    cv::Mat img(10, 10, CV_8UC1, cv::Scalar::all(255));
    EXPECT_ANY_THROW(histogram(img));
}
