#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class InputHandler {
public:
    InputHandler(std::string path1, std::string path2);
    
    std::vector<cv::Mat> getImages(int pathNum = 1) const;
    
    std::vector<std::string> getFilePaths(int pathNum = 1) const;
    
    std::string getPathFromParser(int pathNum = 1) const;
private:
    void readImages(std::string path, int pathNum);
    
    std::string _path1;
    std::string _path2;
    
    std::vector<cv::Mat> _images1;
    std::vector<cv::Mat> _images2;
    
    std::vector<std::string> _paths1;
    std::vector<std::string> _paths2;
};
