#include "detectText.h"

void decodeOutput(const cv::Mat &scores, const cv::Mat &geometry, float minConfidence, std::vector<cv::RotatedRect> &rects, std::vector<float> &confScores)
{
    int rectsHeight = scores.size[2];
    int rectsWidth = scores.size[3];

    for (int i = 0; i < rectsHeight; ++i) {
        const float *scoresData = scores.ptr<float>(0, 0, i);
        const float *x0Data = geometry.ptr<float>(0, 0, i);
        const float *x1Data = geometry.ptr<float>(0, 1, i);
        const float *x2Data = geometry.ptr<float>(0, 2, i);
        const float *x3Data = geometry.ptr<float>(0, 3, i);
        const float *angleData = geometry.ptr<float>(0, 4, i);

        for (int j = 0; j < rectsWidth; ++j) {
            float score = scoresData[j];
            if (score >= minConfidence) {
                float offsetX = j * 4;
                float offsetY = i * 4;

                float angle = angleData[j];
                float sinAngle = std::sin(angle);
                float cosAngle = std::cos(angle);

                float rectangleHeight = x0Data[j] + x2Data[j];
                float rectangleWidth = x1Data[j] + x3Data[j];

                float endX = offsetX + (cosAngle * x1Data[j]) + (sinAngle * x2Data[j]);
                float endY = offsetY - (sinAngle * x1Data[j]) + (cosAngle * x2Data[j]);
                cv::Point2f offset(endX, endY);

                cv::Point2f p1 = cv::Point2f(-sinAngle * rectangleHeight, -cosAngle * rectangleHeight) + offset;
                cv::Point2f p3 = cv::Point2f(-cosAngle * rectangleWidth, sinAngle * rectangleWidth) + offset;
                cv::RotatedRect rect(0.5f * (p1 + p3), cv::Size2f(rectangleWidth, rectangleHeight), -angle * 180.0f / CV_PI);

                rects.push_back(rect);
                confScores.push_back(score);
            }
        }
    }
}

std::vector<cv::Mat> detectText(cv::Mat image, std::string path)
{
    std::vector<cv::Mat> result;

    if (image.empty()) {
        return result;
    }

    static cv::dnn::Net net = cv::dnn::readNet(path);

    float minConfidence = 0.5;
    float NMSThreshold = 0.4;
    int width = 320;
    int height = 320;
    
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(width, height));

    std::vector<cv::Mat> layers;
    std::vector<std::string> layerNames = {"feature_fusion/Conv_7/Sigmoid", "feature_fusion/concat_3"};

    cv::Mat blob;
    cv::dnn::blobFromImage(resized, blob, 1.0, cv::Size(width, height), cv::Scalar(123.68, 116.78, 103.94), true, false);
    net.setInput(blob);
    net.forward(layers, layerNames);

    cv::Mat scores = layers.at(0);
    cv::Mat geometry = layers.at(1);

    std::vector<cv::RotatedRect> rects;
    std::vector<float>confidenceScores;

    decodeOutput(scores, geometry, minConfidence, rects, confidenceScores);

    std::vector<int> indicies;
    cv::dnn::NMSBoxes(rects, confidenceScores, minConfidence, NMSThreshold, indicies);

    float ratioWidth = image.cols / (float)width;
    float ratioHeight = image.rows / (float)height;

    for (int i = 0; i < indicies.size(); ++i) {
        cv::RotatedRect& rect = rects[indicies[i]];

        rect.size.width *= ratioWidth;
        rect.size.height *= ratioHeight;
        rect.center.x *= ratioWidth;
        rect.center.y *= ratioHeight;

        cv::Mat cropped = rotatedRectToMat(rect, image);

        cv::Point2f sourceVertices[4];
        rect.points(sourceVertices);

        for (int i = 0; i < 4; ++i) {
            cv::line(image, sourceVertices[i], sourceVertices[(i + 1) % 4], cv::Scalar(0, 255, 0), 1);
        }

        result.push_back(cropped);
    }

    return result;
}

cv::Mat rotatedRectToMat(cv::RotatedRect rect, cv::Mat image)
{
    cv::Rect boundingRectangle = rect.boundingRect();

    if (boundingRectangle.x < 0 || boundingRectangle.y < 0 || boundingRectangle.x + boundingRectangle.width > image.cols || boundingRectangle.y + boundingRectangle.height > image.rows) {
        cv::copyMakeBorder(image, image, boundingRectangle.height, boundingRectangle.height, boundingRectangle.width, boundingRectangle.width, cv::BORDER_REPLICATE);
        rect.center.x += boundingRectangle.width;
        rect.center.y += boundingRectangle.height;
    }

    cv::Point2f sourceVertices[4];
    rect.points(sourceVertices);

    cv::Point2f distanceVertices[4] = {cv::Point2f(0, rect.size.height - 1),
                                       cv::Point2f(0, 0),
                                       cv::Point2f(rect.size.width - 1, 0),
                                       cv::Point2f(rect.size.width - 1, rect.size.height - 1)};

    cv::Mat matrix = cv::getPerspectiveTransform(sourceVertices, distanceVertices);
    cv::Mat warped;
    cv::warpPerspective(image, warped, matrix, cv::Size(rect.size.width, rect.size.height));
    return warped;
}

std::vector<std::vector<cv::Mat>> detectText(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<std::vector<cv::Mat>> result;

    for (int i = 0; i < images.size(); ++i) {
        std::vector<cv::Mat> resultI = detectText(images.at(i));
        result.push_back(resultI);
    }

    return result;
}