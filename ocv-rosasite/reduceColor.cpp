#include "reduceColor.h"

cv::Mat calculateLookUpTable(int divideWith)
{
    cv::Mat lookUpTable(1, 256, CV_8U);

    if (divideWith == 0) {
        divideWith = 1;
    }

    for (int i = 0; i < 256; ++i) {
        lookUpTable.at<uint8_t>(0, i) = (i / divideWith) * divideWith;
    }

    return lookUpTable;
}

void trackbarCallback(int divideWith, void* userdata)
{
    userData *usrdata = (userData*) userdata;

    if (usrdata->src->empty()) {
        throw std::runtime_error("souce is empty");
    }

    cv::Mat lookuptable = calculateLookUpTable(divideWith);
    *(usrdata->result) = getColorReducedImage(usrdata->src, &lookuptable);
}

cv::Mat reduceColor(cv::Mat image)
{
    if (image.empty()) {
        throw std::runtime_error("Could not process source image!");
    }

    cv::Mat result;
    userData usrdata = {&image, &result, 150};

    cv::Mat table = calculateLookUpTable(usrdata.divideWith);
    result = getColorReducedImage(&image, &table);

    cv::createTrackbar("Trackbar", "result", &usrdata.divideWith, 255, trackbarCallback, &usrdata);

    cv::waitKey(0);
    return result;
}

cv::Mat getColorReducedImage(cv::Mat *image, cv::Mat *lookUpTable)
{
    cv::Mat result;
    cv::LUT(*image, *lookUpTable, result);

    if (result.empty()) {
        throw std::runtime_error("result is empty!");
    }

    cv::imshow("result", result);
    return result;
}

std::vector<cv::Mat> reduceColor(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat>result;

    for (int i = 0; i < images.size(); ++i) {
        cv::Mat resultI = reduceColor(images.at(i));
        result.push_back(resultI);
    }

    if (result.size() == 1) {
        cv::imshow("result", result.at(0));
        cv::waitKey(0);
    }

    return result;
}
