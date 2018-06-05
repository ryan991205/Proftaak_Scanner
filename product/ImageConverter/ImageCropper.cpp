#include "ImageCropper.h"
#include "ReferencePointFinder.h"

#include <iostream>
#include <stdio.h>

#define cropOffset 20

Point2i ImageCropper::CropToEdgePoints(cv::Mat* outputImage, cv::Mat inputImage) 
{
	ReferencePointFinder* refFinder = new ReferencePointFinder();
	std::vector<cv::Point2i> edgePoints = refFinder->GetEdgePoints(inputImage);

	cv::Rect roi = FindRegionOfInterest(edgePoints);
	Point2i offset;

	offset.x = roi.x;
	offset.y = roi.y;
	
	cv::Mat out = inputImage.clone();
	*outputImage = out(roi);

	delete refFinder;

	return offset;
}


cv::Rect ImageCropper::FindRegionOfInterest(std::vector<cv::Point2i> referencePoints)
{
	if(referencePoints.size() < 4)
	{
		throw std::invalid_argument("referencePoints");
	}

	int low_X =  referencePoints.at(0).x;
	int high_X = referencePoints.at(0).x;
	for(uint i = 1; i < referencePoints.size() ; i++)
	{
		if(referencePoints.at(i).x > high_X )
		{
			high_X = referencePoints.at(i).x;
		}

		if(referencePoints.at(i).x < low_X )
		{
			low_X = referencePoints.at(i).x;
		}
	}

	int low_y =  referencePoints.at(0).y;
	int high_y  = referencePoints.at(0).y;
	for(uint i = 1; i < referencePoints.size() ; i++)
	{
		if(referencePoints.at(i).y > high_y )
		{
			high_y = referencePoints.at(i).y;
		}

		if(referencePoints.at(i).y < low_y )
		{
			low_y = referencePoints.at(i).y;
		}
	}

    cv::Rect roi;
    roi.x = low_X + cropOffset; 
    roi.y = low_y + cropOffset;
    roi.height = high_y - low_y - cropOffset*2;
	roi.width = high_X - low_X - cropOffset*2;

	return roi;
}