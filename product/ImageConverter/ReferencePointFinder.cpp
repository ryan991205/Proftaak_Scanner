#include "ReferencePointFinder.h"
#include "ColorFilter.h"

#include <stdexcept>
#include <opencv2/imgproc.hpp> 

// DEBUG
#include <iostream>
#include <stdio.h>
#include <opencv2/highgui.hpp>

#define EXPECTED_REFERENCEVECTORS 4 	// four points of paper

 Point2i ReferencePointFinder::Find(cv::Mat image)
{
	std::vector<cv::Vec3f> referenceVectors;
	cv::GaussianBlur(image, image, cv::Size(9, 9), 2, 2);
	cv::HoughCircles(image, referenceVectors, CV_HOUGH_GRADIENT, 1, image.rows/8, 100, 10, 0, 0);

	Point2i p;

	if(referenceVectors.size() != 1)
	{
		return p;
	}
	cv::Point2i center(std::ceil(referenceVectors[0][0]), 
					   std::ceil(referenceVectors[0][1]));

	
	p.x = center.x;
	p.y = center.y;
	
	return p;
}


Point2i ReferencePointFinder::GetBeginPointMaze(cv::Mat image) 
{
	cv::Mat filteredImage = ColorFilter::GetFilteredImage(Blue,image);
	return Find(filteredImage);
}


Point2i ReferencePointFinder::GetEndPointMaze(cv::Mat image)
{
	cv::Mat filteredImage = ColorFilter::GetFilteredImage(Green,image);
	return Find(filteredImage);
}


std::vector<cv::Point2i> ReferencePointFinder::GetEdgePoints(cv::Mat image) 
{
	cv::Mat filteredImage = ColorFilter::GetFilteredImage(Red,image);
	
	cv::GaussianBlur(filteredImage, filteredImage, cv::Size(9, 9), 2, 2);

	std::vector<cv::Vec3f> referenceVectors;
	cv::HoughCircles(filteredImage, referenceVectors, CV_HOUGH_GRADIENT, 1, 
					 filteredImage.rows/8, 100, 20, 0, 0);

  	if(referenceVectors.size() != EXPECTED_REFERENCEVECTORS)
  	{	
    	throw std::out_of_range("referenceVectors");
  	}

 	 std::vector<cv::Point2i> referencePoints;

  	// calculate centerPoint of referencepoints
  	for(size_t current_referenceVectors = 0; current_referenceVectors < referenceVectors.size(); ++current_referenceVectors) 
 	{
 		cv::Point2i center(std::ceil(referenceVectors[current_referenceVectors][0]), 
		 				   std::ceil(referenceVectors[current_referenceVectors][1]));
    	referencePoints.push_back(center);
  	}
  return referencePoints;
}










