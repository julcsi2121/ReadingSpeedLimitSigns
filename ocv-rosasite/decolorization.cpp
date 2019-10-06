#include "decolorization.h"

cv::Mat decoloring(cv::Mat image)
{
    cv::Mat decoloredImage;
    cv::Mat colorBoosted;
    cv::decolor(image, decoloredImage, colorBoosted);
    return decoloredImage;
}

std::vector<cv::Mat> decoloring(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;
    for (int i = 0; i < images.size(); i++) {
        result.push_back(decoloring(images.at(i)));

    }
    if (result.size() == 1) {
        cv::imshow("Window", result.at(0));
        cv::waitKey(0);
    }
    return result;
}
