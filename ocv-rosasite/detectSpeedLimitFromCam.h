#pragma once
#include "inputHandler.hpp"
#include <opencv2/opencv.hpp>
#include "detectCircle.h"
#include "detectText.h"
#include "readSpeedLimitSign.h"


void detectSpeedLimitFromCam(const std::string port);
