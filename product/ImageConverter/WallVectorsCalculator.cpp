
#include "WallVectorsCalculator.h"
#include <opencv2/imgproc.hpp>
#include <algorithm>

// debug 
#include <opencv2/highgui.hpp> 
#include <iostream>
#include <stdio.h>

void WallVectorsCalculator::Draw(cv::Mat* image, std::vector<Line> Walls )
{
    if(image == NULL)
    {
        //throw  
    }

    cv::Mat outputImage = *image;
    

    for(size_t selectedWall = 0; selectedWall < Walls.size(); ++selectedWall)
    {
        cv::Point2i bP = cv::Point2i(Walls.at(selectedWall).beginPoint.x,Walls.at(selectedWall).beginPoint.y);
        cv::Point2i eP = cv::Point2i(Walls.at(selectedWall).endPoint.x,Walls.at(selectedWall).endPoint.y);

        //cv::Mat outputImage = *image;
        // zal nu nog error geven.
        cv::line(outputImage, bP, eP, cv::Scalar(40, 150, 40), 3, CV_AA);
        *image = outputImage;
    }
    return;
}

void  WallVectorsCalculator::Calculate(std::vector<Line>* outputWalls, std::vector<Line> gridLines, cv::Mat image, int wallThreshold)
{
    WallThreshold = wallThreshold;
    if(outputWalls == NULL)
    {
       // trow
    }

    if(image.data == NULL)
    {
        // trow
    }

    cv::Mat img;
    cv::cvtColor(image, img, CV_BGR2GRAY);

    std::vector<int>* horizontalGridLines = new std::vector<int>();
    std::vector<int>* verticalGridLines   = new std::vector<int>();
    SortLinesOnRotation(horizontalGridLines, verticalGridLines, gridLines);

    std::vector<Line> wallsOnLine;
    for(size_t line = 0; line < horizontalGridLines->size(); ++line) 
    {
        wallsOnLine = getAllHorizontalWallsFromLine(horizontalGridLines->at(line), verticalGridLines, img); 
        outputWalls->insert(outputWalls->end(),wallsOnLine.begin(),wallsOnLine.end());    
    }

    for(size_t line = 0; line < verticalGridLines->size(); ++line) 
    {
        wallsOnLine = getAllVerticalWallsFromLine(verticalGridLines->at(line), horizontalGridLines, img);
        outputWalls->insert(outputWalls->end(),wallsOnLine.begin(),wallsOnLine.end());
    }

    delete horizontalGridLines;
    delete verticalGridLines;
    return;
}


std::vector<Line> WallVectorsCalculator::getAllHorizontalWallsFromLine(int line, const std::vector<int> *verticalLines, cv::Mat image)
{
    std::vector<Line> MazeWalls;
    Point2i beginpointReadout;
    Line currentWallSection;
    
    bool newWallSection = true;

    currentWallSection.beginPoint.y    = line;
    currentWallSection.endPoint.y      = line;
    beginpointReadout.y                = line;

    for(size_t currentGridLine = 0; currentGridLine < verticalLines->size(); ++currentGridLine) 
 	{
        if(currentGridLine + 1 >= verticalLines->size())
        {  
            if(currentWallSection.beginPoint.x != currentWallSection.endPoint.x)
            {
                MazeWalls.push_back(currentWallSection);
            }
            return MazeWalls;
        }
     
        if(newWallSection)
        {
            currentWallSection.beginPoint.x =  verticalLines->at(currentGridLine);
            newWallSection = false;
        }

        currentWallSection.endPoint.x = verticalLines->at(currentGridLine + 1);
        beginpointReadout.x =  verticalLines->at(currentGridLine);

        if(!WallExistsOnPosition(beginpointReadout, currentWallSection.endPoint, image))
        {
            currentWallSection.endPoint.x = verticalLines->at(currentGridLine);
            if(currentWallSection.beginPoint.x != currentWallSection.endPoint.x)
            {
                MazeWalls.push_back(currentWallSection);         
            } 
            newWallSection = true; 
        }   
    }
    // should not be called
    return MazeWalls;
}


std::vector<Line> WallVectorsCalculator::getAllVerticalWallsFromLine(int line,  const std::vector<int> *horizontalLines, cv::Mat image)
{
   std::vector<Line> MazeWalls;
    Point2i beginpointReadout;
    Line currentWallSection;
    
    bool newWallSection = true;

    currentWallSection.beginPoint.x    = line;
    currentWallSection.endPoint.x      = line;
    beginpointReadout.x                = line;

    for(size_t currentGridLine = 0; currentGridLine < horizontalLines->size(); ++currentGridLine) 
 	{
        if(currentGridLine + 1 >= horizontalLines->size())
        {
            if(currentWallSection.beginPoint.y != currentWallSection.endPoint.y)
            {
                MazeWalls.push_back(currentWallSection);
            }
            return MazeWalls;
        }

        if(newWallSection)
        {
            currentWallSection.beginPoint.y =  horizontalLines->at(currentGridLine);
            newWallSection = false;
        }
   
        currentWallSection.endPoint.y = horizontalLines->at(currentGridLine + 1);
        beginpointReadout.y =  horizontalLines->at(currentGridLine);

        if(!WallExistsOnPosition(beginpointReadout, currentWallSection.endPoint, image))
        {
            currentWallSection.endPoint.y = horizontalLines->at(currentGridLine);
            if(currentWallSection.beginPoint.y != currentWallSection.endPoint.y)
            {
                MazeWalls.push_back(currentWallSection);
            }
            newWallSection = true; 
        }    
    }
    // should not be called
    return MazeWalls;
}


// pre-conditions :  image.type == CV_8U
bool WallVectorsCalculator::WallExistsOnPosition(Point2i beginPos, Point2i endPos, cv::Mat image)
{
    cv::Point2i MeasurePoint =  cv::Point2i( (beginPos.x + endPos.x) / 2,
                                             (beginPos.y + endPos.y) / 2); 

    if(image.at<uchar>(MeasurePoint) < (uint)WallThreshold)
    {
        return true;
    }
    return false;
}


void WallVectorsCalculator::SortLinesOnRotation(std::vector<int>* horizontal, std::vector<int>* vertical, std::vector<Line> inputLines)
{
    for (size_t i = 0; i < inputLines.size(); i++)
	{
        if(inputLines.at(i).beginPoint.x == inputLines.at(i).endPoint.x)
        {
            vertical->push_back(inputLines.at(i).beginPoint.x);
        }
        else
        {
            horizontal->push_back(inputLines.at(i).beginPoint.y);
        }
	}
    sort( horizontal->begin(), horizontal->end() );
    sort( vertical->begin()  , vertical->end() );
    return;
}