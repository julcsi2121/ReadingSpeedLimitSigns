#include "gtest/gtest.h"
#include "salty.h"

TEST(SaltEffectTest, DifferentInputOutput)
{
    cv::Mat src(100, 100, CV_8UC1, cv::Scalar(0));
    cv::Mat result;
    userDataSalty userdata = {src, result};
    salt(6, &userdata);
    int srcWhitePixels = cv::countNonZero(userdata.src);
    int resultWhitePixels = cv::countNonZero(userdata.result);

    EXPECT_LT(srcWhitePixels, resultWhitePixels);
}