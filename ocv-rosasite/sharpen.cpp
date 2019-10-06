#include "sharpen.h"

cv::Mat sharpen(cv::Mat src)
{
    if (src.empty()) {
        throw std::runtime_error("Mat object is empty!");
    }

    cv::Mat result;
    cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    cv::filter2D(src, result, src.depth(), kernel);

    return result;
}

std::vector<cv::Mat> sharpen(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat>resultVector;

    for (int i = 0; i < images.size(); ++i) {
        cv::Mat resultI = sharpen(images.at(i));
        resultVector.push_back(resultI);
    }

    if (resultVector.size() == 1) {
        cv::imshow("result", resultVector.at(0));
        cv::waitKey(0);
    }

    return resultVector;
}
