#ifndef REFERENCEPOINTFINDER_H
#define REFERENCEPOINTFINDER_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "scannerCore.h"

class ReferencePointFinder 
{
private:
	Point2i Find(cv::Mat image);

public:

	ReferencePointFinder() {};
	Point2i GetBeginPointMaze(cv::Mat image);
	Point2i GetEndPointMaze(cv::Mat image);

	std::vector<cv::Point2i> GetEdgePoints(cv::Mat image);
};

#endif
