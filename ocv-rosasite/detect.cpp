#include "detect.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include "readText.hpp"
#include "separateColor.h"
using namespace cv;
using namespace cv::dnn;

void decode(const Mat& scores, const Mat& geometry, float scoreThresh,
    std::vector<RotatedRect>& detections, std::vector<float>& confidences);

cv::Mat rotatedRectToMatt(cv::RotatedRect rect, cv::Mat image);

int detect()
{
    // Load network.
    Net net = readNet("../models/frozen_east_text_detection.pb");
    // Open a video file or an image file or a camera stream.
    VideoCapture cap(0);
    
    int inpWidth = 160;
    int inpHeight = 160;

    float confThreshold = 0.5;
    float nmsThreshold = 0.4;

    static const std::string kWinName = "EAST: An Efficient and Accurate Scene Text Detector";
    namedWindow(kWinName);
    std::vector<Mat> outs;
    std::vector<String> outNames(2);
    outNames[0] = "feature_fusion/Conv_7/Sigmoid";
    outNames[1] = "feature_fusion/concat_3";
    Mat frame, blob;
    while (waitKey(1) < 0)
    {
        cap >> frame;
        if (frame.empty())
        {
            waitKey();
            break;
        }
        blobFromImage(frame, blob, 1.0, Size(inpWidth, inpHeight), Scalar(123.68, 116.78, 103.94), true, false);
        net.setInput(blob);
        net.forward(outs, outNames);
        Mat scores = outs[0];
        Mat geometry = outs[1];
        // Decode predicted bounding boxes.
        std::vector<RotatedRect> boxes;
        std::vector<float> confidences;
        decode(scores, geometry, confThreshold, boxes, confidences);
        // Apply non-maximum suppression procedure.
        std::vector<int> indices;
        NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
        // Render detections.
        Point2f ratio((float)frame.cols / inpWidth, (float)frame.rows / inpHeight);
        for (size_t i = 0; i < indices.size(); ++i)
        {
            RotatedRect& box = boxes[indices[i]];
            Point2f vertices[4];
            box.points(vertices);
            for (int j = 0; j < 4; ++j)
            {
                vertices[j].x *= ratio.x;
                vertices[j].y *= ratio.y;
            }
            for (int j = 0; j < 4; ++j) {
                line(frame, vertices[j], vertices[(j + 1) % 4], Scalar(0, 255, 0), 1);
            }
            
            cv::Mat cropped = rotatedRectToMatt(box, frame);

                std::vector<cv::Mat> colors = separateColor(cropped);
                //cv::imshow("3", colors.at(2));
                cv::Mat grey;
                cv::cvtColor(colors.at(2), grey, cv::COLOR_BGR2GRAY);

                //cv::imshow("grey", grey);

                cv::Mat binary;
                cv::threshold(grey, binary, 0, 255, cv::THRESH_OTSU);
                cv::Mat opened;
                cv::morphologyEx(binary, opened, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
                cv::Mat closed;
                cv::morphologyEx(opened, closed, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));


                std::string text = readText(closed);
                std::cout << text << std::endl;
        }
        // Put efficiency information.
        std::vector<double> layersTimes;
        double freq = getTickFrequency() / 1000;
        double t = net.getPerfProfile(layersTimes) / freq;
        std::string label = format("Inference time: %.2f ms", t);
        putText(frame, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
        imshow(kWinName, frame);
    }
    return 0;
}
void decode(const Mat& scores, const Mat& geometry, float scoreThresh,
    std::vector<RotatedRect>& detections, std::vector<float>& confidences)
{
    detections.clear();
    CV_Assert(scores.dims == 4); CV_Assert(geometry.dims == 4); CV_Assert(scores.size[0] == 1);
    CV_Assert(geometry.size[0] == 1); CV_Assert(scores.size[1] == 1); CV_Assert(geometry.size[1] == 5);
    CV_Assert(scores.size[2] == geometry.size[2]); CV_Assert(scores.size[3] == geometry.size[3]);
    const int height = scores.size[2];
    const int width = scores.size[3];
    for (int y = 0; y < height; ++y)
    {
        const float* scoresData = scores.ptr<float>(0, 0, y);
        const float* x0_data = geometry.ptr<float>(0, 0, y);
        const float* x1_data = geometry.ptr<float>(0, 1, y);
        const float* x2_data = geometry.ptr<float>(0, 2, y);
        const float* x3_data = geometry.ptr<float>(0, 3, y);
        const float* anglesData = geometry.ptr<float>(0, 4, y);
        for (int x = 0; x < width; ++x)
        {
            float score = scoresData[x];
            if (score < scoreThresh)
                continue;
            // Decode a prediction.
            // Multiple by 4 because feature maps are 4 time less than input image.
            float offsetX = x * 4.0f, offsetY = y * 4.0f;
            float angle = anglesData[x];
            float cosA = std::cos(angle);
            float sinA = std::sin(angle);
            float h = x0_data[x] + x2_data[x];
            float w = x1_data[x] + x3_data[x];
            Point2f offset(offsetX + cosA * x1_data[x] + sinA * x2_data[x],
                offsetY - sinA * x1_data[x] + cosA * x2_data[x]);
            Point2f p1 = Point2f(-sinA * h, -cosA * h) + offset;
            Point2f p3 = Point2f(-cosA * w, sinA * w) + offset;
            RotatedRect r(0.5f * (p1 + p3), Size2f(w, h), -angle * 180.0f / (float)CV_PI);
            detections.push_back(r);
            confidences.push_back(score);
        }
    }
}

cv::Mat rotatedRectToMatt(cv::RotatedRect rect, cv::Mat image)
{
    cv::Rect boundingRectangle = rect.boundingRect();

    if (boundingRectangle.x < 0 || boundingRectangle.y < 0 || boundingRectangle.x + boundingRectangle.width > image.cols || boundingRectangle.y + boundingRectangle.height > image.rows) {
        cv::copyMakeBorder(image, image, boundingRectangle.height, boundingRectangle.height, boundingRectangle.width, boundingRectangle.width, cv::BORDER_REPLICATE);
        rect.center.x += boundingRectangle.width;
        rect.center.y += boundingRectangle.height;
    }

    cv::Point2f sourceVertices[4];
    rect.points(sourceVertices);

    cv::Point2f distanceVertices[4] = { cv::Point2f(0, rect.size.height - 1),
                                       cv::Point2f(0, 0),
                                       cv::Point2f(rect.size.width - 1, 0),
                                       cv::Point2f(rect.size.width - 1, rect.size.height - 1) };

    cv::Mat matrix = cv::getPerspectiveTransform(sourceVertices, distanceVertices);
    cv::Mat warped;
    cv::warpPerspective(image, warped, matrix, cv::Size(rect.size.width, rect.size.height));
    return warped;
}
