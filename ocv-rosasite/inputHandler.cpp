#include "inputHandler.hpp"
#include <filesystem>

InputHandler::InputHandler(std::string path1, std::string path2)
{
    _path1 = path1;
    _path2 = path2;
    
    if (!_path1.empty())
        readImages(_path1, 1);
    else
        std::runtime_error("No path to file or folder");
    
    if (!_path2.empty())
        readImages(_path2, 2);
}

void InputHandler::readImages(std::string path, int pathNum)
{
    bool isDir = std::filesystem::is_directory(path);
    
    if (!isDir) {
        cv::Mat singleImage = cv::imread(path);
        if (!singleImage.data) {
            throw std::runtime_error("Can not read the image!");
        }
        
        if (pathNum == 1) {
            _images1.push_back(singleImage);
            _paths1.push_back(path);
        } else {
            _images2.push_back(singleImage);
            _paths2.push_back(path);
        }
        
    } else {
        cv::Mat singleImage;
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                singleImage = cv::imread(entry.path());
                if (!singleImage.data) {
                    throw std::runtime_error("Can not read the image!");
                }
                
                if (pathNum == 1) {
                    _images1.push_back(singleImage);
                    _paths1.push_back(path);
                } else {
                    _images2.push_back(singleImage);
                    _paths2.push_back(path);
                }
            }
        }
    }
}

std::vector<cv::Mat> InputHandler::getImages(int pathNum) const
{
    if (pathNum == 1) {
        return _images1;
    } else {
        return _images2;
    }
}

std::vector<std::string> InputHandler::getFilePaths(int pathNum) const
{
    if (pathNum == 1) {
        return _paths1;
    } else {
        return _paths2;
    }
}

std::string InputHandler::getPathFromParser(int pathNum) const
{
    if (pathNum == 1) {
        return _path1;
    } else {
        return _path2;
    }
}
