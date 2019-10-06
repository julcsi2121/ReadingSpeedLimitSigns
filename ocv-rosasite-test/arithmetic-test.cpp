#include "gtest/gtest.h"
#include "arithmetic.h"

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

TEST(ArithmeticOperationTest, ScalarMultiplication)
{
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::Mat result = multiplyWithScalar(image1, 5);

    EXPECT_EQ_MAT(result, image1 * 5);
}

TEST(ArithmeticOperationTest, ScalarMultiplicationWithNegativeNumber)
{
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::Mat result = multiplyWithScalar(image1, -2);

    EXPECT_EQ_MAT(result, image1 * -2);
}

TEST(ArithmeticOperationTest, AddingMats)
{
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2(2, 2, CV_8UC3, cv::Scalar(255, 150, 45));
    cv::Mat result = addMats(image1, image2);

    EXPECT_EQ_MAT(addMats(image1, image2), result);
}

TEST(ArithmeticOperationTest, AddingDifferentTypeMats)
{
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2(2, 2, CV_8UC1, cv::Scalar(255));

    EXPECT_ANY_THROW(addMats(image1, image2));
}

TEST(ArithmeticOperationTest, SubtractingMats)
{
    cv::Mat result;
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2(2, 2, CV_8UC3, cv::Scalar(255, 150, 55));
    result = subtractMats(image1, image2);

    EXPECT_EQ_MAT(subtractMats(image1, image2), result);
}

TEST(ArithmeticOperationTest, SubtractingDifferentTypeMats)
{
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2(2, 2, CV_8UC1, cv::Scalar(255));

    EXPECT_ANY_THROW(subtractMats(image1, image2));
}

TEST(ArithmeticOperationTest, MultiplicationOfMats)
{
    cv::Mat result;
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2(2, 2, CV_8UC3, cv::Scalar(255, 150, 55));
    result = multiplyMats(image1, image2);

    EXPECT_EQ_MAT(multiplyMats(image1, image2), result);
}

TEST(ArithmeticOperationTest, MultiplicationOfDifferentTypeMats)
{
    cv::Mat image1(2, 2, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2(2, 2, CV_8UC1, cv::Scalar(255));

    EXPECT_ANY_THROW(multiplyMats(image1, image2));
}
