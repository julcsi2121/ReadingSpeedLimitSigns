#include "detectEdges.h"

cv::Mat detectEdges(cv::Mat image)
{
    if (image.empty()) {
        std::runtime_error("source is empty!\n");
    }

    cv::Mat result;
    cv::Mat grey;
    
    if (image.type() != 0) {
        cv::cvtColor(image, grey, cv::COLOR_BGR2GRAY);
    }
    else {
        grey = image.clone();
    }
    
    userDataDetectEdges usrdata = { grey, result, 100, 200};

    cannyEdgeDetection(&usrdata);
    cv::imshow("Edge Detection", usrdata.result);

    cv::createTrackbar("Min", "Edge Detection", &usrdata.tresholdMin, 255, trackbarCallbackMin, &usrdata);
    cv::createTrackbar("Max", "Edge Detection", &usrdata.tresholdMax, 255, trackbarCallbackMax, &usrdata);

    cv::waitKey(0);
    return usrdata.result;
}

void trackbarCallbackMin(int min, void *userdata)
{
    userDataDetectEdges *usrdata = (userDataDetectEdges*)userdata;
    cannyEdgeDetection(usrdata);
    cv::imshow("Edge Detection", usrdata->result);
}

void trackbarCallbackMax(int max, void *userdata)
{
    userDataDetectEdges *usrdata = (userDataDetectEdges*)userdata;
    cannyEdgeDetection(usrdata);
    cv::imshow("Edge Detection", usrdata->result);
}

void cannyEdgeDetection(userDataDetectEdges *userdata)
{
    cv::Canny(userdata->src, userdata->result, userdata->tresholdMin, userdata->tresholdMax);
}

std::vector<cv::Mat> detectEdges(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;

    for (int i = 0; i < images.size(); ++i) {
        cv::Mat resultI = detectEdges(images.at(i));
        result.push_back(resultI);
    }

    return result;
}
