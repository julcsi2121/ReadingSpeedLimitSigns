#include "resizeAndRotate.h"

cv::Mat resizeAndRotate(cv::Mat image)
{
    UserDataForResizeAndRotate userdata;
    userdata.src = image;

    cv::imshow("Rotated and Resized Image", image);

    cv::createTrackbar("Angle", "Rotated and Resized Image", &userdata.angle, 360, resizeAndRotateTrackbarCallback, &userdata);
    cv::createTrackbar("Scale", "Rotated and Resized Image", &userdata.scale, 100, resizeAndRotateTrackbarCallback, &userdata);

    cv::waitKey(0);

    return userdata.result;
}

std::vector<cv::Mat> resizeAndRotate(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> newImages;

    for (int i = 0; i < images.size(); ++i) {
        newImages.push_back(resizeAndRotate(images[i]));
    }

    return newImages;
}

void resizeAndRotateTrackbarCallback(int pos, void* ud)
{
    UserDataForResizeAndRotate* userdata = (UserDataForResizeAndRotate*) ud;

    if (userdata->scale == 0) {
        userdata->scale = 1;
    }

    cv::Mat rotatedAndResizedImage = getRotatedAndResizedImage(userdata->src, userdata->angle, userdata->scale);

    cv::imshow("Rotated and Resized Image", rotatedAndResizedImage);

    userdata->result = rotatedAndResizedImage;
}

cv::Mat getRotatedAndResizedImage(cv::Mat image, int angle, int scale)
{
    cv::Mat matRotation = cv::getRotationMatrix2D(cv::Point(image.cols / 2, image.rows / 2), angle, scale / 50.0);

    cv::Mat rotatedAndResizedImage;

    cv::warpAffine(image, rotatedAndResizedImage, matRotation, image.size(), cv::INTER_LINEAR, 0, cv::Scalar());

    return rotatedAndResizedImage;
}
