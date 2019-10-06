#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "opencv2/opencv.hpp"

#include "inputHandler.hpp"
#include "decolorization.h"
#include "sharpen.h"
#include "separateColor.h"
#include "reduceColor.h"
#include "wave.hpp"
#include "imageMorphology.hpp"
#include "arithmetic.h"
#include "cartoonEffect.h"
#include "detectEdges.h"
#include "histogram.hpp"
#include "panorama.h"
#include "resizeAndRotate.h"
#include "salty.h"
#include "detectCorners.h"
#include "readText.hpp"
#include "detectCircle.h"
#include "detectText.h"
#include "setupMode.hpp"
#include "readSpeedLimitSign.h"
#include "detectSpeedLimitFromCam.h"
#include "loadPreset.hpp"

void help();
void collectResults(std::vector<cv::Mat> results, std::vector<cv::Mat> *collector);
void outputHandler(std::vector<cv::Mat> images, std::string savePath);

const char* keys =
{
    "{help h         |        | show help message                   }"
    "{save s         | <none> | save image                          }"
    "{decolor        | <none> | decolorize an image                 }"
    "{sharpen        | <none> | sharpen an image                    }"
    "{separateColor  | <none> | separates the colors                }"
    "{reduceColor    | <none> | reduce the colors of images         }"
    "{wave           | <none> | creates wave effect on images       }"
    "{dilate         | <none> | makes line thicker                  }"
    "{erode          | <none> | makes line thinner                  }"
    "{open           | <none> | remove background noise from images }"
    "{close          | <none> | remove noise from object            }"
    "{add            | <none> | add 2 images                        }"
    "{subtract       | <none> | subtract 2 images                   }"
    "{multiplyMatrix | <none> | multiply 2 images as matrix         }"
    "{multiplyScalar | <none> | multiply 2 images as scalar         }"
    "{cartoon        | <none> | apply cartoon effect to images      }"
    "{edges          | <none> | detect edges in images              }"
    "{histogram      | <none> | create images' histogram            }"
    "{panorama       | <none> | create panorama picture from images }"
    "{resizeAndRotate| <none> | resize and rotate images            }"
    "{salt           | <none> | apply salt effect to images         }"
    "{corners        | <none> | finds potential corners in image    }"
    "{readText       | <none> | OCR text from images to strigs      }"
    "{circles        | <none> | detect circles in images            }"
    "{detectText     | <none> | detect text in images               }"
    "{speedSign      | <none> | detect speed limit sign from picture}"
    "{live           | <none> | detect speed limit signs from cam   }"
    "{setup          | <none> | setup speed limit sign detection    }"
    "{parameters     | <none> | load preset parameters              }"
    "{@path1         | <none> | path1 for a file or dir             }"
    "{@path2         | <none> | path2 for a file or dir             }"
};

int main(int argc, char *argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);

    if (!parser.check()) {
        parser.printErrors();
        return -1;
    } else if (parser.has("help")) {
        help();
        return 0;
    }

    std::string path1 = parser.get<std::string>("@path1");
    std::string path2 = parser.get<std::string>("@path2");

    std::vector<cv::Mat> results;
    std::vector<cv::Mat> resultCollector;
    
    InputHandler inputHandler(path1, path2);

    try {

        if (parser.has("decolor")) {
            results = decoloring(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("sharpen")) {
            results = sharpen(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("separateColor")) {
            results = separateColor(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("reduceColor")) {
            results = reduceColor(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("wave")) {
            results = wave(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("dilate")) {
            results = dilate(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("erode")) {
            results = erode(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("open")) {
            results = open(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("close")) {
            results = close(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("add")) {
            results = addMats(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("subtract")) {
            results = subtractMats(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("multiplyMatrix")) {
            results = multiplyMats(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("multiplyScalar")) {
            results = multiplyWithScalar(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("cartoon")) {
            results = cartoonEffect(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("edges")) {
            results = detectEdges(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("histogram")) {
            results = histogram(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("panorama")) {
            results = panorama(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("resizeAndRotate")) {
            results = resizeAndRotate(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("salt")) {
            results = saltEffect(inputHandler);
            collectResults(results, &resultCollector);
        }

        if (parser.has("corners")) {
            results = detectCorners(inputHandler);
            collectResults(results, &resultCollector);
        }
        
        if (parser.has("readText")) {
            readText(inputHandler);
        }

        if (parser.has("circles")) {
            detectCircle(inputHandler);
        }

        if (parser.has("detectText")) {
            detectText(inputHandler);
        }
        
        if (parser.has("speedSign")) {
            readSpeedLimitSign(inputHandler);
        }
        
        if (parser.has("live")) {
            std::string port = parser.get<std::string>("live");
            if (port == "true") {
                port = "none";
            }
            detectSpeedLimitFromCam(port);
        }
        
        if (parser.has("setup")) {
            std::string presetName = parser.get<std::string>("setup");
            if (presetName == "true") {
                presetName = "undefined";
            }
            setup(presetName);
        }

        if (parser.has("parameters")) {
            std::string preset = parser.get<std::string>("parameters");
            if (preset == "true") {
                throw std::runtime_error("You not specified any preset.");
            }
            loadPreset(preset);
        }
        
        if (parser.has("save")) {
            std::string savePath = parser.get<std::string>("save");
            if (savePath == "true") {
                throw std::runtime_error("Can not save, path is empty!");
            }
            outputHandler(resultCollector, savePath);
        }

    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
}

void help()
{
    std::cout
        << "\n------------------------------------------------------------------\n"
        << " This program was made by GFA Ferrilata Rosasite OpencCV students:\n"
        << "     Varga Julia | Varga Jozsef | Varga Viktor | Horvath Donat\n\n"
        << " Usage: \n"
        << "        -save -s            save generated images \n"
        << "        -decolor            decolorize images \n"
        << "        -sharpen            sharpen images \n"
        << "        -separateColor      separates the colors of images \n"
        << "        -reduceColor		reduce the colors of images \n"
        << "        -wave				creates wave effect on images \n"
        << "        -dilate				makes lines thicker \n"
        << "        -erode				makes lines thinner \n"
        << "        -open				remove backround noise from image \n"
        << "        -close              remove noise from object \n"
        << "        -add                add 2 images \n"
        << "        -subtract           subtract 2 images \n"
        << "        -multiplyMatrix     multiply 2 images as matrix \n"
        << "        -multiplyScalar     multiply 2 images as scalar \n"
        << "        -cartoon            apply cartoon effect to images \n"
        << "        -edges              detect edges in images \n"
        << "        -histogram          create images' histogram \n"
        << "        -panorama           create panorama picture from images \n"
        << "        -resizeAndRotate    resize and rotate images \n"
        << "        -salt               apply salt effect to images \n"
        << "        -corners            finds potential corners in image \n"
        << "        -circles            finds potential circles in image \n"
        << "        -detectText         finds potential text boxes in image \n"
        << "        -setup              set and save the given parameters for speed limit sign detection \n"
        << "        -speedSign          finds potential speed limit signs on image \n"
        << "        -live               finds potential speed limit signs from live camera input \n"
        << "        -parameters         load preset parameters from the database if exist \n"
        << "------------------------------------------------------------------\n\n"
        << std::endl;
}

void collectResults(std::vector<cv::Mat> results, std::vector<cv::Mat> *collector)
{
    for (int i = 0; i < results.size(); i++) {
        collector->push_back(results.at(i));
    }
}

void outputHandler(std::vector<cv::Mat> images, std::string savePath)
{
    bool isDir = std::filesystem::is_directory(savePath);
    if (isDir) {
        for (int i = 0; i < images.size(); i++) {
            std::string filePath = savePath + "ocv_output_" + std::to_string(i) + ".jpg";
            cv::imwrite(filePath, images.at(i));
        }
    } else {
        cv::imwrite(savePath, images.at(0));
    }
}
