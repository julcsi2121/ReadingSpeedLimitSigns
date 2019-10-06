#include "panorama.h"

cv::Mat panorama(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;

    cv::Mat panoramaPicture;

    cv::Ptr<cv::Stitcher> stitcherObject = cv::Stitcher::create(mode);

    cv::Stitcher::Status status = stitcherObject->stitch(images, panoramaPicture);

    if (status != cv::Stitcher::OK) {
        throw std::runtime_error("Can't stitch images!");
    }

    cv::imshow("Panorama Picture", panoramaPicture);

    cv::waitKey(0);

    return panoramaPicture;
}
