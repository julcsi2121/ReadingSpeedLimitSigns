#pragma once

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <string>

class OCR {
public:
    OCR(bool isWordToRecognize);
    ~OCR();
    std::string getText(cv::Mat *image);
private:
    tesseract::TessBaseAPI *ocr;
};
