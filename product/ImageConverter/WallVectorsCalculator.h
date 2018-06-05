#ifndef WALLVECTORSCALCULATOR_H
#define WALLVECTORSCALCULATOR_H

#include <vector>
#include <exception>
#include <opencv2/core/core.hpp>

#include "scannerCore.h"

class WallVectorsCalculator 
{
private:
    int WallThreshold;


    bool WallExistsOnPosition(Point2i beginPos, Point2i endPos, cv::Mat image);
    std::vector<Line> getAllHorizontalWallsFromLine(int line, const std::vector<int> *directionGrid, cv::Mat image);
    std::vector<Line> getAllVerticalWallsFromLine(int line, const std::vector<int> *directionGrid, cv::Mat image);
    void SortLinesOnRotation(std::vector<int>* horizontal,std::vector<int>* vertical , std::vector<Line> inputLines);
    
public:
    //WallVectorsCalculator();
    void Calculate(std::vector<Line>* outputWalls, std::vector<Line> gridLines, cv::Mat image, int wallThreshold);
    void Draw(cv::Mat* image, std::vector<Line> Walls);
};

#endif

