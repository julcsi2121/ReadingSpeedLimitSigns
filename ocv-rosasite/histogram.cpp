#include "histogram.hpp"

cv::Mat histogram(cv::Mat image, bool editMode)
{
    if (image.channels() != 3) {
        throw std::runtime_error("Histogram function is for RGB (3 channel) images only!");
    }
    
    std::vector<cv::Mat> channelsBGR;
    cv::split(image, channelsBGR);
    
    int size = 256;
    float range[] = {0, 256} ;
    const float* histRange = {range};
    
    bool uniform = true; bool accumulate = false;
    
    cv::Mat blueHist, greenHist, redHist;
    
    cv::calcHist(&channelsBGR.at(0), 1, 0, cv::Mat(), blueHist, 1, &size, &histRange, uniform, accumulate);
    cv::calcHist(&channelsBGR.at(1), 1, 0, cv::Mat(), greenHist, 1, &size, &histRange, uniform, accumulate);
    cv::calcHist(&channelsBGR.at(2), 1, 0, cv::Mat(), redHist, 1, &size, &histRange, uniform, accumulate);
    
    int histWidth = 768; int histHeight = 600;
    int binWidth = cvRound((double) histWidth/size);
    
    cv::Mat histogram(histHeight, histWidth, CV_8UC3, cv::Scalar::all(0));
    
    cv::Mat blueLayer(histHeight, histWidth, CV_8UC1, cv::Scalar::all(0));
    cv::Mat greenLayer(histHeight, histWidth, CV_8UC1, cv::Scalar::all(0));
    cv::Mat redLayer(histHeight, histWidth, CV_8UC1, cv::Scalar::all(0));
    
    normalize(blueHist, blueHist, 0, histogram.rows, cv::NORM_MINMAX, -1, cv::Mat());
    normalize(greenHist, greenHist, 0, histogram.rows, cv::NORM_MINMAX, -1, cv::Mat());
    normalize(redHist, redHist, 0, histogram.rows, cv::NORM_MINMAX, -1, cv::Mat());
    
    for (int i = 1; i < size; i++) {
        if (editMode) {
            line(histogram, cv::Point(binWidth* (i-1), histHeight - cvRound(blueHist.at<float>(i-1))) ,
                 cv::Point(binWidth*(i), histHeight - cvRound(blueHist.at<float>(i))),
                 cv::Scalar(255, 0, 0), 1, cv::LINE_AA, 0);
            line(histogram, cv::Point(binWidth* (i-1), histHeight - cvRound(greenHist.at<float>(i-1))) ,
                 cv::Point(binWidth*(i), histHeight - cvRound(greenHist.at<float>(i))),
                 cv::Scalar(0, 255, 0), 1, cv::LINE_AA, 0);
            line(histogram, cv::Point(binWidth* (i-1), histHeight - cvRound(redHist.at<float>(i-1))) ,
                 cv::Point(binWidth*(i), histHeight - cvRound(redHist.at<float>(i))),
                 cv::Scalar(0, 0, 255), 1, cv::LINE_AA, 0);
        } else {
            cv::Point bluePoint1 = cv::Point(binWidth * (i - 1), histHeight);
            cv::Point bluePoint2 = cv::Point(binWidth * i, histHeight);
            cv::Point bluePoint3 = cv::Point(binWidth * i, histHeight - cvRound(blueHist.at<float>(i)));
            cv::Point bluePoint4 = cv::Point(binWidth * (i - 1), histHeight - cvRound(blueHist.at<float>(i-1)));
            cv::Point bluePoints[] = {bluePoint1, bluePoint2, bluePoint3, bluePoint4, bluePoint1};
            
            fillConvexPoly(blueLayer, bluePoints, 5, cv::Scalar::all(255));
            
            cv::Point greenPoint1 = cv::Point(binWidth * (i - 1), histHeight);
            cv::Point greenPoint2 = cv::Point(binWidth * i, histHeight);
            cv::Point greenPoint3 = cv::Point(binWidth * i, histHeight - cvRound(greenHist.at<float>(i)));
            cv::Point greenPoint4 = cv::Point(binWidth * (i - 1), histHeight - cvRound(greenHist.at<float>(i-1)));
            cv::Point greenPoints[] = {greenPoint1, greenPoint2, greenPoint3, greenPoint4, greenPoint1};
            
            fillConvexPoly(greenLayer, greenPoints, 5, cv::Scalar::all(255));
            
            cv::Point redPoint1 = cv::Point(binWidth * (i - 1), histHeight);
            cv::Point redPoint2 = cv::Point(binWidth * i, histHeight);
            cv::Point redPoint3 = cv::Point(binWidth * i, histHeight - cvRound(redHist.at<float>(i)));
            cv::Point redPoint4 = cv::Point(binWidth * (i - 1), histHeight - cvRound(redHist.at<float>(i-1)));
            cv::Point redPoints[] = {redPoint1, redPoint2, redPoint3, redPoint4, redPoint1};
            
            fillConvexPoly(redLayer, redPoints, 5, cv::Scalar::all(255));
            
            for (int i = 0; i < histogram.rows; i++) {
                for (int j = 0; j < histogram.cols; j++) {
                    histogram.at<cv::Vec3b>(i, j)[0] = blueLayer.at<uint8_t>(i, j);
                    histogram.at<cv::Vec3b>(i, j)[1] = greenLayer.at<uint8_t>(i, j);
                    histogram.at<cv::Vec3b>(i, j)[2] = redLayer.at<uint8_t>(i, j);
                }
            }
        }
    }
    
    return histogram;
}

std::vector<cv::Mat> histogram(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
    std::vector<cv::Mat> result;
    
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    
    for (int i = 0; i < images.size(); i++) {

        TrackbarData trackbarData;
        trackbarData.image = &(images.at(i));
       
        cv::createTrackbar("Brigthness", "Image", &trackbarData.brigthness, 100, brigthnessCallback, &trackbarData);
        cv::createTrackbar("Contrast", "Image", &trackbarData.contrast, 100, contrastCallback, &trackbarData);
        cv::setTrackbarPos("Brigthness", "Image", trackbarData.brigthness);
        cv::setTrackbarPos("Contrast", "Image", trackbarData.contrast);

        cv::imshow("Image", images.at(i));
        cv::imshow("Histogram", histogram(images.at(i)));

        if (cv::waitKey(0) == 27) {
            break;
        }
        
        images.at(i).convertTo(trackbarData.result, -1, trackbarData.contrast / 50.0, trackbarData.brigthness * 2 - 100);
        result.push_back(histogram(trackbarData.result, false));
    }
    
    return result;
}

void brigthnessCallback(int brigthness, void* userData)
{
    TrackbarData* usrData = (TrackbarData*) userData;
    
    usrData->image->convertTo(usrData->result, -1, usrData->contrast / 50.0, brigthness * 2 - 100);
    cv::imshow("Image", usrData->result);
    cv::imshow("Histogram", histogram(usrData->result));
}

void contrastCallback(int contrast, void* userData)
{
    TrackbarData* usrData = (TrackbarData*) userData;
    
    usrData->image->convertTo(usrData->result, -1, contrast / 50.0, usrData->brigthness * 2 - 100);
    cv::imshow("Image", usrData->result);
    cv::imshow("Histogram", histogram(usrData->result));
}
