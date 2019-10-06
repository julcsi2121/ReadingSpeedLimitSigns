#include "gtest/gtest.h"
#include "sharpen.h"

static void EXPECT_EQ_MAT(cv::Mat m1, cv::Mat m2)
{
    EXPECT_EQ(m1.size, m2.size);
    EXPECT_EQ(m1.type(), m2.type());

    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            EXPECT_EQ(m1.at<uint8_t>(i, j), m2.at<uint8_t>(i, j));
        }
    }
}

TEST(SharpenTests, TestEmptyMat)
{
    cv::Mat src;
    EXPECT_ANY_THROW(sharpen(src));
}

TEST(SharpenTests, TestMatWithOnesReturnsTheSame)
{
    cv::Mat src = cv::Mat::ones(10, 10, CV_8UC1);
    cv::Mat result = sharpen(src);
    EXPECT_EQ_MAT(src, result);
}

TEST(SharpenTests, TestKernelWithSimpleMatrix)
{
    cv::Mat src = (cv::Mat_<uint8_t>(3, 3) << 1, 1, 1, 1, 2, 1, 1, 1, 1);
    cv::Mat expectedResult = (cv::Mat_<uint8_t>(3, 3) << 1, 0, 1, 0, 6, 0, 1, 0, 1);

    cv::Mat result = sharpen(src);

    EXPECT_EQ_MAT(expectedResult, result);
}
