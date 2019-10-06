#include "wave.hpp"
#include <cmath>

cv::Mat wave(cv::Mat image)
{
    cv::Mat result;

    cv::Mat srcX(image.rows, image.cols, CV_32F);
    cv::Mat srcY(image.rows, image.cols, CV_32F);

    for (int j = 0; j < image.rows; j++) {
        for (int k = 0; k < image.cols; k++) {
            srcX.at<float>(j, k) = k;
            srcY.at<float>(j, k) = j + 5 * sin(k / 10.0);
        }
    }

    cv::remap(image, result, srcX, srcY, cv::INTER_LINEAR);

    return result;
}

std::vector<cv::Mat> wave(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> result;
    std::vector<cv::Mat> images = inputHandler.getImages();
    for (int i = 0; i < images.size(); i++) {
        result.push_back(wave(images.at(i)));
    }

    if (images.size() == 1) {
        cv::imshow("Original", images.at(0));
        cv::imshow("Wave", result.at(0));
        cv::waitKey(0);
    }

    return result;
}
