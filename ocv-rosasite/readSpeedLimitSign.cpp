#include "readSpeedLimitSign.h"

int readSpeedLimitSign(cv::Mat image, userDataForSpeedLimitReading userData, FilterSignLimit &filter)
{
    int result = 0;
    int filteredResult = 0;
    std::vector<cv::Vec3i> circles = circleDetection(image, userData.maximumDistance, userData.cannyEdgeUpperTreshold, userData.centerDetectionTreshold, userData.minRad, userData.maxRad);

    for (int i = 0; i < circles.size(); ++i) {
        int circleX = circles[i][0];
        int circleY = circles[i][1];
        int radius = circles[i][2];

        cv::circle(image, {circleX, circleY}, radius, cv::Scalar(255, 0, 0), 3);

        cv::Rect boundingRect = cv::Rect(circleX - radius, circleY - radius, 2 * radius, 2 * radius);
        boundingRect &= cv::Rect(cv::Point(0, 0), image.size());
        cv::Mat cropped = image(boundingRect);

        std::vector<cv::Mat> text = detectText(cropped);

        for (int j = 0; j < text.size(); ++j) {
            std::vector<cv::Mat> colors = separateColor(text.at(j));
            cv::Mat grey;

            cv::cvtColor(colors.at(2), grey, cv::COLOR_BGR2GRAY);

            cv::Mat binary;
            cv::threshold(grey, binary, 0, 255, cv::THRESH_OTSU);
            cv::Mat opened;
            cv::morphologyEx(binary, opened, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(userData.kernelSize, userData.kernelSize)));
            cv::Mat closed;
            cv::morphologyEx(opened, closed, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(userData.kernelSize, userData.kernelSize)));

            std::string detectedText = readText(closed, userData.border);

            if (!detectedText.empty()) {
                try {
                    result = std::stoi(detectedText);
                    filteredResult = filter.addRecord(result);
                }
                catch (std::exception) {
                }
            }
        }
    }

    if (!circles.empty() && result != 0) {
        std::cout << "speed: " << result << std::endl;
        std::cout << "filtered: " << filteredResult << std::endl;
    }
    return filteredResult;
}

std::vector<int> readSpeedLimitSign(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<int> result;

    for (int i = 0; i < images.size(); ++i) {
        userDataForSpeedLimitReading userData;
        FilterSignLimit filter(2);
        int speedSign = readSpeedLimitSign(images.at(i), userData, filter);
        result.push_back(speedSign);
    }

    return result;
}
