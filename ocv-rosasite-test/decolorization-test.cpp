#include "gtest/gtest.h"
#include "decolorization.h"

TEST(DecolorTest, DifferentTypeOfInputAndOutput)
{
    cv::Mat image(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat result = decoloring(image);

    EXPECT_NE(image.type(), result.type());
}

TEST(DecolorTest, SizeIsTheSame)
{
    cv::Mat image(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat result = decoloring(image);

    EXPECT_EQ(image.size(), result.size());
}
