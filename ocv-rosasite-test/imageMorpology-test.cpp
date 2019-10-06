#include <gtest/gtest.h>
#include "imageMorphology.hpp"

TEST(Dilate, testIfWhitePixelIsMore)
{
    cv::Mat img(500, 500, CV_8UC1);
    img = 0;

    for (int i = 0; i < img.cols; i++) {
        img.at<uint8_t>(250, i) = 255;
    }

    cv::Mat result = dilate(img);

    int whitePixels = 0;

    for (int i = 0; i < result.cols; i++) {
        for (int j = 0; j < result.rows; j++) {
            if (result.at<uint8_t>(j, i) == 255) {
                whitePixels++;
            }
        }
    }

    EXPECT_EQ(whitePixels, img.cols * 5);
}

TEST(Erode, testIfWhitePixelIsZero)
{
    cv::Mat img(500, 500, CV_8UC1);
    img = 0;

    for (int i = 0; i < img.cols; i++) {
        img.at<uint8_t>(250, i) = 255;
    }

    cv::Mat result = erode(img);

    int whitePixels = 0;

    for (int i = 0; i < result.cols; i++) {
        for (int j = 0; j < result.rows; j++) {
            if (result.at<uint8_t>(j, i) == 255) {
                whitePixels++;
            }
        }
    }

    EXPECT_EQ(whitePixels, 0);
}

TEST(Open, testIfWhitePixelIsGone)
{
    cv::Mat img(500, 500, CV_8UC1);
    img = 0;

    for (int i = 0; i < img.cols; i++) {
        img.at<uint8_t>(248, i) = 255;
        img.at<uint8_t>(249, i) = 255;
        img.at<uint8_t>(250, i) = 255;
        img.at<uint8_t>(251, i) = 255;
        img.at<uint8_t>(252, i) = 255;
        img.at<uint8_t>(253, i) = 255;
    }

    img.at<uint8_t>(100, 100) = 255;

    cv::Mat result = open(img);

    int whitePixels = 0;

    for (int i = 0; i < result.cols; i++) {
        for (int j = 0; j < result.rows; j++) {
            if (result.at<uint8_t>(j, i) == 255) {
                whitePixels++;
            }
        }
    }

    EXPECT_EQ(whitePixels, img.cols * 6);
}

TEST(Close, testIfWhiteLineFilled)
{
    cv::Mat img(500, 500, CV_8UC1);
    img = 0;

    for (int i = 0; i < img.cols; i++) {
        img.at<uint8_t>(248, i) = 255;
        img.at<uint8_t>(253, i) = 255;
    }

    cv::Mat result = close(img);

    int whitePixels = 0;

    for (int i = 0; i < result.cols; i++) {
        for (int j = 0; j < result.rows; j++) {
            if (result.at<uint8_t>(j, i) == 255) {
                whitePixels++;
            }
        }
    }

    EXPECT_EQ(whitePixels, img.cols * 6);
}
