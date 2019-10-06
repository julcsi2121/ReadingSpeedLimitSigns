#include "gtest/gtest.h"
#include "reduceColor.h"

static void EXPECT_EQ_MAT_C3(cv::Mat m1, cv::Mat m2)
{
    EXPECT_EQ(m1.size, m2.size);
    EXPECT_EQ(m1.type(), m2.type());

    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            EXPECT_EQ(m1.at<cv::Vec3b>(i, j), m2.at<cv::Vec3b>(i, j));
        }
    }
}

static void EXPECT_EQ_MAT_C1(cv::Mat m1, cv::Mat m2)
{
    EXPECT_EQ(m1.size, m2.size);
    EXPECT_EQ(m1.type(), m2.type());

    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            EXPECT_EQ(m1.at<uint8_t>(i, j), m2.at<uint8_t>(i, j));
        }
    }
}

TEST(ReduceColorTests, LookupTableContainsCorrectValue)
{
    cv::Mat table = calculateLookUpTable(10);
    uint8_t expectedValue = 0;

    EXPECT_EQ(table.at<uint8_t>(0, 34) % 10, expectedValue);
}

TEST(ReduceColorTests, LookupTableWithZero)
{
    cv::Mat table = calculateLookUpTable(0);
    uint8_t expectedValue = 7;

    EXPECT_EQ(table.at<uint8_t>(0, 7), expectedValue);
}

TEST(ReduceColorTests, LookupTableWithNegativeNumber)
{
    cv::Mat table = calculateLookUpTable(-2);
    uint8_t expectedValue = 6;

    EXPECT_EQ(table.at<uint8_t>(0, 7), expectedValue);
}

TEST(ReduceColorTests, LookupTableWithLargeNumber)
{
    cv::Mat table = calculateLookUpTable(1000);
    uint8_t expectedValue = 0;

    EXPECT_EQ(table.at<uint8_t>(0, 231), expectedValue);
}

TEST(ReduceColorTests, ReduceColorHandlesEmptySource)
{
    cv::Mat src;

    EXPECT_ANY_THROW(reduceColor(src));
}

TEST(ReduceColorTests, ReduceColorHandlesSimpleInput)
{
    cv::Mat src(3, 3, CV_8UC3, cv::Vec3b(7, 12, 57));
    cv::Mat lookuptable = calculateLookUpTable(10);
    cv::Mat result = getColorReducedImage(&src, &lookuptable);

    cv::Mat expected(3, 3, CV_8UC3, cv::Vec3b(0, 10, 50));

    EXPECT_EQ_MAT_C3(result, expected);
}

TEST(ReduceColorTests, ReduceColorHandlesNotEmptyResult)
{
    cv::Mat src(3, 3, CV_8UC3, cv::Vec3b(7, 12, 57));
    cv::Mat lookuptable = calculateLookUpTable(10);
    cv::Mat result(5, 5, CV_8UC3, cv::Vec3b(124, 210, 32));
    result = getColorReducedImage(&src, &lookuptable);

    cv::Mat expected(3, 3, CV_8UC3, cv::Vec3b(0, 10, 50));

    EXPECT_EQ_MAT_C3(result, expected);
}

TEST(ReduceColorTests, ReduceColorHandles1C)
{
    cv::Mat src = (cv::Mat_<uint8_t>(2, 2) << 12, 12, 12, 12);
    cv::Mat lookuptable = calculateLookUpTable(10);
    cv::Mat result = getColorReducedImage(&src, &lookuptable);

    cv::Mat expected = (cv::Mat_<uint8_t>(2, 2) << 10, 10, 10, 10);

    EXPECT_EQ_MAT_C1(result, expected);
}
