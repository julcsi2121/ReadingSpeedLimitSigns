#include "salty.h"

cv::Mat saltEffect(cv::Mat src)
{
    int amount = 20;
    cv::Mat result = src.clone();
    userDataSalty userData = {src, result};

    salt(amount, &userData);
    cv::imshow("result", userData.result);
    cv::createTrackbar("Salt", "result", &amount, 100, saltTrackbarCallback, &userData);

    cv::waitKey(0);
    return userData.result;
}

std::vector<cv::Mat> saltEffect(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> results;

    for (int i = 0; i < images.size(); i++) {
        cv::Mat result = saltEffect(images[i]);
        results.push_back(result);
    }
    if (results.size() == 1) {
        cv::imshow("salt", results[0]);
        cv::waitKey(0);
    }
    return results;
}

void saltTrackbarCallback(int amount, void *userdata)
{
    userDataSalty *userD = (userDataSalty*) userdata;
    salt(amount, userD);
    cv::imshow("result", userD->result);
}

void salt(int amount, userDataSalty *userdata)
{
    userdata->result = userdata->src.clone();
    for (int i = 0; i < amount * userdata->result.rows * userdata->result.cols / 1000; i++) {
        int rndNumRows = rand() % userdata->result.rows;
        int rndNumCols = rand() % userdata->result.cols;
        if (userdata->result.type() == CV_8UC1) {
            userdata->result.at<uint8_t>(rndNumRows, rndNumCols) = 255;
        } else if (userdata->result.type() == CV_8UC3) {
            userdata->result.at<cv::Vec3b>(rndNumRows, rndNumCols) = {255, 255, 255};
        }
    }
}
