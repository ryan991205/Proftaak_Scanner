#ifndef COLORFILTER_H
#define COLORFILTER_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV

enum Color { Blue, Green, Red };

 class ColorFilter 
{

private:
	ColorFilter() {}

public:
	static cv::Mat GetFilteredImage(Color color, cv::Mat image);
};

#endif
