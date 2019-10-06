#include "readText.hpp"
#include <gtest/gtest.h>

TEST(ReadTextTest, testWithSingleWordLowerCase)
{
    std::string result, text;
    text = "text";
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
    
    cv::Mat img(textSize.height + 25, textSize.width + 25, CV_8UC1, cv::Scalar::all(255));
    cv::putText(img, text, cv::Point2f(25,25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(0));
    
    result = readText(img, 10, false);
    
    EXPECT_EQ(result, text + '\n');
}

TEST(ReadTextTest, testWithSingleWordAllCap)
{
    std::string result, text;
    text = "TEXT";
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
    
    cv::Mat img(textSize.height + 25, textSize.width + 25, CV_8UC1, cv::Scalar::all(255));
    cv::putText(img, text, cv::Point2f(25,25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(0));
    
    result = readText(img, 10, false);
    
    EXPECT_EQ(result, text + '\n');
}

TEST(ReadTextTest, testWithColorfulSingleWordOnColoredBackground)
{
    std::string result, text;
    text = "CoLoRs";
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
    
    cv::Mat img(textSize.height + 25, textSize.width + 25, CV_8UC3, cv::Scalar(150, 210, 17));
    cv::putText(img, text, cv::Point2f(25,25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(128, 56, 110));
    
    result = readText(img, 10, false);
    
    EXPECT_EQ(result, text + '\n');
}

TEST(ReadTextTest, testWithSingleLineText)
{
    std::string result, text;
    text = "Hello world, this is OCR!";
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
    
    cv::Mat img(textSize.height + 25, textSize.width + 25, CV_8UC1, cv::Scalar::all(255));
    cv::putText(img, text, cv::Point2f(25,25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(0));
    
    result = readText(img, 10, false);
    
    EXPECT_EQ(result, text + '\n');
}

TEST(ReadTextTest, testWithMultipleLineText)
{
    std::string result, line1, line2;
    line1 = "OMG, sooo much OCR. Such WOW!";
    line2 = "Is this magic or what?";
    cv::Size textSize = cv::getTextSize(line1, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
    
    cv::Mat img(textSize.height * 2 + 25, textSize.width + 25, CV_8UC1, cv::Scalar::all(255));
    cv::putText(img, line1, cv::Point2f(25, 25), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(0));
    cv::putText(img, line2, cv::Point2f(25, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(0));

    result = readText(img, 10, false);
    
    EXPECT_EQ(result, line1 + '\n' + line2 + '\n');
}

TEST(ReadTextTest, testWithNoBorder)
{
    std::string result, text;
    text = "BordlessnessStress";
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
    
    cv::Mat img(textSize.height, textSize.width, CV_8UC1, cv::Scalar::all(255));
    cv::putText(img, text, cv::Point2f(0, textSize.height - 1), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar::all(0));
    
    result = readText(img, 10, false);
    
    EXPECT_EQ(result, text + '\n');
}
