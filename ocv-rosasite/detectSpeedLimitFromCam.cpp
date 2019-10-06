#include "detectSpeedLimitFromCam.h"
#include "serialConnection.hpp"

void detectSpeedLimitFromCam(const std::string port)
{
    userDataForSpeedLimitReading userdata;
    FilterSignLimit filtering(2);

    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        throw std::runtime_error("Can not open webcam");
    }
    
    SerialConnection connection;
    if (port != "none") {
        connection.setPort(port);
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;

        int speed = readSpeedLimitSign(frame, userdata, filtering);
        
        if (port != "none")
            connection.send(std::to_string(speed));

        if (cv::waitKey(30) >= 0) {
            break;
        }

        cv::imshow("cirles", frame);
    }
}
