#include "separateColor.h"

std::vector<cv::Mat> separateColor(cv::Mat image)
{
    std::vector<cv::Mat> newImages;
    cv::Vec3b pixel;

    cv::Mat blueImage(image.rows, image.cols, CV_8UC3);
    cv::Mat greenImage(image.rows, image.cols, CV_8UC3);
    cv::Mat redImage(image.rows, image.cols, CV_8UC3);

    for (int j = 0; j < image.rows; ++j) {
        for (int k = 0; k < image.cols; ++k) {
            pixel[0] = image.at<cv::Vec3b>(j, k)[0];
            pixel[1] = 0;
            pixel[2] = 0;
            blueImage.at<cv::Vec3b>(j, k) = pixel;
        }
    }

    for (int j = 0; j < image.rows; ++j) {
        for (int k = 0; k < image.cols; ++k) {
            pixel[0] = 0;
            pixel[1] = image.at<cv::Vec3b>(j, k)[1];
            pixel[2] = 0;
            greenImage.at<cv::Vec3b>(j, k) = pixel;
        }
    }

    for (int j = 0; j < image.rows; ++j) {
        for (int k = 0; k < image.cols; ++k) {
            pixel[0] = 0;
            pixel[1] = 0;
            pixel[2] = image.at<cv::Vec3b>(j, k)[2];
            redImage.at<cv::Vec3b>(j, k) = pixel;
        }
    }

    newImages.push_back(blueImage);
    newImages.push_back(greenImage);
    newImages.push_back(redImage);

    return newImages;
}

std::vector<cv::Mat> separateColor(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> newImages;

    for (int i = 0; i < images.size(); ++i) {
        std::vector<cv::Mat> buffer = separateColor(images[i]);

        for (int j = 0; j < buffer.size(); ++j) {
            newImages.push_back(buffer[j]);
        }
    }

    if (images.size() == 1) {
        cv::imshow("blueImage", newImages[0]);
        cv::imshow("greenImage", newImages[1]);
        cv::imshow("redImage", newImages[2]);
        cv::imshow("originalImage", images[0]);

        cv::waitKey(0);
    }

    return newImages;
}
