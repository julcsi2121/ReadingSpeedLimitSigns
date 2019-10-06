#include "detectCircle.h"

cv::Mat outputImage(std::vector<cv::Vec3i> circles, cv::Mat sourceImage)
{
    cv::Mat output = sourceImage.clone();

    int circleCounter = circles.size();

    for (size_t i = 0; i < circles.size(); i++) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

        int radius = cvRound(circles[i][2]);

        cv::circle(output, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);

        std::string area = std::to_string((int) ((radius * radius) * 3.14));

        cv::putText(output, area, center, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, (255, 255, 255), 2);
        cv::putText(output, area, center, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, (0, 0, 0), 1);

        std::cout << "circles: " << circleCounter << std::endl;

        cv::circle(output, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }
    return output;
}

void detectCircleTrackbarCallback(int, void* ud)
{
    userDataForDetectCircle* userdata = (userDataForDetectCircle*) ud;

    std::vector<cv::Vec3i> circlesDetected = circleDetection(userdata->src, userdata->maximumDistance, userdata->cannyEdgeUpperTreshold, userdata->centerDetectionTreshold);

    cv::Mat circlesOnImage = outputImage(circlesDetected, userdata->src);

    cv::imshow("Circles", circlesOnImage);

    userdata->circles = circlesDetected;
}

std::vector<cv::Vec3i> detectCircle(cv::Mat image)
{
    userDataForDetectCircle userdata;
    userdata.src = image;

    cv::imshow("Circles", image);

    cv::createTrackbar("MaxDis", "Circles", &userdata.maximumDistance, userdata.src.rows, detectCircleTrackbarCallback, &userdata);
    cv::createTrackbar("EdgeTresh", "Circles", &userdata.cannyEdgeUpperTreshold, 200, detectCircleTrackbarCallback, &userdata);
    cv::createTrackbar("CenterDet", "Circles", &userdata.centerDetectionTreshold, 100, detectCircleTrackbarCallback, &userdata);

    detectCircleTrackbarCallback(0, &userdata);

    cv::waitKey(0);

    return userdata.circles;
}

std::vector<cv::Vec3i> sortedRadiusWithCoordinates(std::vector<cv::Vec3f> circles)
{
    std::vector<int> allRadius;
    std::vector<cv::Vec3i> descendingSortedCircles;
    std::map<int, std::vector<cv::Point>> radiusWithCoordinates;

    for (int i = 0; i < circles.size(); i++) {
        allRadius.push_back(circles[i][2]);
    }

    shellSort(allRadius, true);

    for (int i = 0; i < circles.size(); i++) {

        cv::Point tempPoint;
        tempPoint.x = circles[i][0];
        tempPoint.y = circles[i][1];

        radiusWithCoordinates[circles[i][2]].push_back(tempPoint);
    }

    for (int i = 0; i < circles.size(); i++) {

        int radius = allRadius[i];
        std::vector<cv::Point> rwc = radiusWithCoordinates[radius];

        for (int j = 0; j < rwc.size(); j++) {

            cv::Vec3i temp;
            temp[0] = (radiusWithCoordinates.at(allRadius[i - j]).at(j).x);
            temp[1] = (radiusWithCoordinates.at(allRadius[i - j]).at(j).y);
            temp[2] = (allRadius.at(i));

            descendingSortedCircles.push_back(temp);

            i++;
        }
    }
    return descendingSortedCircles;
}

std::vector<cv::Vec3i> circleDetection(cv::Mat image, int minimumDistance, int cannyEdgeUpperTreshold, int centerDetectionTreshold, int minRad, int maxRad)
{
    cv::Mat resultImage = image.clone();
    std::vector<cv::Vec3i> circlesInDescendingOrder;

    cv::Mat grayPicture;
    cv::cvtColor(resultImage, grayPicture, cv::COLOR_BGR2GRAY);

    cv::Mat bluredPicture;
    GaussianBlur(grayPicture, bluredPicture, cv::Size(9, 9), 2, 2);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(bluredPicture, circles, cv::HOUGH_GRADIENT, 1, bluredPicture.rows / minimumDistance, cannyEdgeUpperTreshold, centerDetectionTreshold, minRad, maxRad);

    circlesInDescendingOrder = sortedRadiusWithCoordinates(circles);

    return circlesInDescendingOrder;
}

std::vector<std::vector<cv::Vec3i>> detectCircle(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<std::vector<cv::Vec3i>> resultVectorForAllimages;

    for (int i = 0; i < images.size(); i++) {
        resultVectorForAllimages.push_back(detectCircle(images[i]));
    }
    return resultVectorForAllimages;
}