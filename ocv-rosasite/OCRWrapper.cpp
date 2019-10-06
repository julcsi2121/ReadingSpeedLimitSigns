#include "OCRWrapper.hpp"

OCR::OCR(bool isWordToRecognize) {
    ocr = new tesseract::TessBaseAPI();
    ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY);

    if (isWordToRecognize) {
        ocr->Init(nullptr, "digits", tesseract::OEM_LSTM_ONLY);
        ocr->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
    }
    else {
        ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY);
        ocr->SetPageSegMode(tesseract::PSM_AUTO);
    }
}

OCR::~OCR() {
    ocr->End();
    delete ocr;
}

std::string OCR::getText(cv::Mat *image) {
    ocr->SetImage(image->data, image->cols, image->rows, 1, int(image->step));
    return std::string(ocr->GetUTF8Text());
}
