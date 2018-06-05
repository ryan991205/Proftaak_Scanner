#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV
#include <opencv2/imgproc.hpp>  	// image processing functions.
#include "scannerCore.h"

class ImageCropper {

public:
	static Point2i CropToEdgePoints(cv::Mat* outputImage, cv::Mat inputImage);
	static cv::Rect FindRegionOfInterest(std::vector<cv::Point2i> referencePoints);
};

#endif
