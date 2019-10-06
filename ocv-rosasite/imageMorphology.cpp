#include "imageMorphology.hpp"

cv::Mat dilate(cv::Mat image)
{
    cv::Mat result;
    cv::dilate(image, result, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    return result;
}

std::vector<cv::Mat> dilate(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;

    for (int i = 0; i < images.size(); i++) {
        result.push_back(dilate(images.at(i)));
    }

    if (images.size() == 1) {
        cv::imshow("Original", images.at(0));
        cv::imshow("Dilate", result.at(0));
        cv::waitKey(0);
    }

    return result;
}

cv::Mat erode(cv::Mat image)
{
    cv::Mat result;
    cv::erode(image, result, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    return result;
}

std::vector<cv::Mat> erode(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;

    for (int i = 0; i < images.size(); i++) {
        result.push_back(erode(images.at(i)));
    }

    if (images.size() == 1) {
        cv::imshow("Original", images.at(0));
        cv::imshow("Erode", result.at(0));
        cv::waitKey(0);
    }

    return result;
}

cv::Mat open(cv::Mat image)
{
    cv::Mat result;
    cv::morphologyEx(image, result, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    return result;
}

std::vector<cv::Mat> open(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;

    for (int i = 0; i < images.size(); i++) {
        result.push_back(open(images.at(i)));
    }

    if (images.size() == 1) {
        cv::imshow("Original", images.at(0));
        cv::imshow("Open", result.at(0));
        cv::waitKey(0);
    }

    return result;
}

cv::Mat close(cv::Mat image)
{
    cv::Mat result;
    cv::morphologyEx(image, result, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));
    return result;
}

std::vector<cv::Mat> close(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;

    for (int i = 0; i < images.size(); i++) {
        result.push_back(close(images.at(i)));
    }

    if (images.size() == 1) {
        cv::imshow("Original", images.at(0));
        cv::imshow("Close", result.at(0));
        cv::waitKey(0);
    }

    return result;
}
