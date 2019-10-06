#include "detectCorners.h"

cv::Mat detectCorners(cv::Mat image)
{
    if (image.empty()) {
        throw std::runtime_error("Couldn't open source image!\n");
    }

    cv::Mat grey;
    cv::Mat result;

    if (image.type() != CV_8UC1) {
        cv::cvtColor(image, grey, cv::COLOR_BGR2GRAY);
    }
    else {
        grey = image;
    }

    UserDataForDetectCorners userData = { grey, result, 200 };
    userData.result = harrisCornerDetection(&userData);

    cv::imshow("result", userData.result);
    cv::createTrackbar("threshold", "result", &userData.threshold, 255, detectCornersTrackbarCallback, &userData);
    cv::waitKey(0);

    return userData.result;
}

void detectCornersTrackbarCallback(int threshold, void* userdata)
{
    UserDataForDetectCorners *userData = (UserDataForDetectCorners*)userdata;
    userData->result = harrisCornerDetection(userData);
    cv::imshow("result", userData->result);
}

cv::Mat harrisCornerDetection(UserDataForDetectCorners *userData)
{
    int block_size = 2;
    int apertureSize = 3;
    double k = 0.06;

    cv::Mat dst = cv::Mat::zeros(userData->src.size(), CV_32FC1);
    cv::cornerHarris(userData->src, dst, block_size, apertureSize, k);

    cv::Mat dst_norm;
    cv::Mat dst_norm_scaled;

    cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
    cv::convertScaleAbs(dst_norm, dst_norm_scaled);

    for (int i = 0; i < dst_norm.rows; ++i) {
        for (int j = 0; j < dst_norm.cols; ++j) {
            if ((int)dst_norm.at<float>(i, j) > userData->threshold) {
                cv::circle(dst_norm_scaled, cv::Point(j, i), 5, cv::Scalar(0));
            }
        }
    }
    
    return dst_norm_scaled;
}

std::vector<cv::Mat> detectCorners(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;

    for (int i = 0; i < images.size(); ++i) {
        cv::Mat resultI = detectCorners(images.at(i));
        result.push_back(resultI);
    }
    
    return result;
}
