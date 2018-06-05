#ifndef GRIDCALCULATOR_H
#define GRIDCALCULATOR_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV
#include "scannerCore.h"

class GridCalculator {
private: 
static cv::Mat FilterImage(cv::Mat image, int kernelSize, int blackwhiteThreshold);
static std::vector<Line> GenerateGrid(cv::Mat filteredImage, int lineThreshold);
static std::vector<Line> ConvertVect2fToLine(std::vector<cv::Vec2f> lines);




public:
GridCalculator();

static std::vector<Line> Calculate(cv::Mat input_image, cv::Mat *output_image, int kernelSize, 
                                                         int blackWhiteThreshold, int lineThreshold);

static cv::Mat Plot(cv::Mat image, std::vector<Line>lines);


};

#endif
