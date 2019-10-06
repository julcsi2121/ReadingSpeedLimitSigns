#include "arithmetic.h"

cv::Mat addMats(cv::Mat image1, cv::Mat image2)
{
    cv::Mat result;
    cv::add(image1, image2, result);
    return result;
}

std::vector<cv::Mat> addMats(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images1 = inputHandler.getImages(1);
    std::vector<cv::Mat> images2 = inputHandler.getImages(2);
    cv::Mat result;
    std::vector<cv::Mat> vectorOfResults;

    if (images1.size() >= images2.size()) {
        for (int i = 0; i < images2.size(); i++) {
            if (images2[i].size() == images1[i].size()) {
                result = addMats(images2[i], images1[i]);
                vectorOfResults.push_back(result);
            } else {
                throw std::runtime_error("Size doesn't match.");
            }
        }
    } else if (images1.size() < images2.size()) {
        for (int i = 0; i < images1.size(); i++) {
            if (images2[i].size() == images1[i].size()) {
                result = addMats(images2[i], images1[i]);
                vectorOfResults.push_back(result);
            } else {
                throw std::runtime_error("Size doesn't match.");
            }
        }
    }
    if (vectorOfResults.size() == 1) {
        cv::imshow("add", vectorOfResults[0]);
        cv::waitKey(0);
    }
    return vectorOfResults;
}

cv::Mat subtractMats(cv::Mat image1, cv::Mat image2)
{
    cv::Mat result;
    cv::subtract(image1, image2, result);
    return result;
}

std::vector<cv::Mat> subtractMats(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images1 = inputHandler.getImages(1);
    std::vector<cv::Mat> images2 = inputHandler.getImages(2);
    cv::Mat result;
    std::vector<cv::Mat> vectorOfResults;

    if (images1.size() >= images2.size()) {
        for (int i = 0; i < images2.size(); i++) {
            if (images2[i].size() == images1[i].size()) {
                result = subtractMats(images2[i], images1[i]);
                vectorOfResults.push_back(result);
            } else {
                throw std::runtime_error("Size doesn't match.");
            }
        }
    } else if (images1.size() < images2.size()) {
        for (int i = 0; i < images1.size(); i++) {
            if (images2[i].size() == images1[i].size()) {
                result = subtractMats(images2[i], images1[i]);
                vectorOfResults.push_back(result);
            } else {
                throw std::runtime_error("Size doesn't match.");
            }
        }
    }
    if (vectorOfResults.size() == 1) {
        cv::imshow("subtract", vectorOfResults[0]);
        cv::waitKey(0);
    }
    return vectorOfResults;
}

cv::Mat multiplyMats(cv::Mat image1, cv::Mat image2)
{
    cv::Mat result;
    cv::multiply(image1, image2, result);
    return result;
}

std::vector<cv::Mat> multiplyMats(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images1 = inputHandler.getImages(1);
    std::vector<cv::Mat> images2 = inputHandler.getImages(2);
    cv::Mat result;
    std::vector<cv::Mat> vectorOfResults;

    if (images1.size() >= images2.size()) {
        for (int i = 0; i < images2.size(); i++) {
            if (images2[i].size() == images1[i].size()) {
                result = multiplyMats(images2[i], images1[i]);
                vectorOfResults.push_back(result);
            } else {
                throw std::runtime_error("Size doesn't match.");
            }
        }
    } else if (images1.size() < images2.size()) {
        for (int i = 0; i < images1.size(); i++) {
            if (images2[i].size() == images1[i].size()) {
                result = multiplyMats(images2[i], images1[i]);
                vectorOfResults.push_back(result);
            } else {
                throw std::runtime_error("Size doesn't match.");
            }
        }
    }
    if (vectorOfResults.size() == 1) {
        cv::imshow("multiply", vectorOfResults[0]);
        cv::waitKey(0);
    }
    return vectorOfResults;
}

cv::Mat multiplyWithScalar(cv::Mat image1, int scalar)
{
    cv::Mat result = image1 * scalar;
    return result;
}

std::vector<cv::Mat> multiplyWithScalar(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    cv::Mat result;
    std::vector<cv::Mat> vectorOfResults;

    for (int i = 0; i < images.size(); i++) {
        result = scalar(images[i]);
    }
    
    return result;
}

void trackBarCallback(int scalar, void *userdata)
{
    arithmeticUserData *userData = (arithmeticUserData*) userdata;
    userData->result = multiplyWithScalar(userData->image, scalar);
    cv::imshow("result", userData->result);
}

cv::Mat scalar(cv::Mat image)
{
    cv::Mat result;
    int scalar = 1;
    arithmeticUserData userData = {image, scalar, result};
    cv::imshow("result", image);
    cv::createTrackbar("Scalar", "result", &scalar, 10, trackBarCallback, &userData);
    cv::waitKey(0);
    return userData.result;
}