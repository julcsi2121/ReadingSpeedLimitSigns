#include <gtest/gtest.h>
#include "wave.hpp"

TEST(WaveTest, testIfOneLineDiffer)
{
    cv::Mat img(50, 50, CV_8UC1);
    img = 0;

    for (int i = 0; i < img.cols; i++) {
        img.at<uint8_t>(25, i) = 255;
    }

    cv::Mat result = wave(img);
    int whitePixels = 0;

    for (int i = 0; i < result.cols; i++) {
        if (result.at<uint8_t>(25, i) == 255) {
            whitePixels++;
        }
    }

    EXPECT_NE(whitePixels, img.cols);
}
