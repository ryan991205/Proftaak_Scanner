
#include "ColorFilter.h"
#include <opencv2/imgproc.hpp>

//debug
#include <opencv2/highgui.hpp> 


cv::Mat ColorFilter::GetFilteredImage(Color color, cv::Mat image) 
{
  cv::Mat lowFilteredImage;
  cv::Mat highFilteredImage;
  switch(color)
  {
	case Blue: //H = 225/2 = 112.5
		cv::inRange(image, cv::Scalar(85, 100, 100), cv::Scalar(112, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(112, 100, 100), cv::Scalar(125, 255, 255), highFilteredImage);
	break;

	case Green: // H = 135/2 = 67.5
		cv::inRange(image, cv::Scalar(55, 100, 100), cv::Scalar(67, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(67, 100, 100), cv::Scalar(75, 255, 255), highFilteredImage);
	break;

	case Red: //H = 0
		cv::inRange(image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), highFilteredImage);
	break;

	default:
		throw std::invalid_argument("color");
	break;
  }

  // combine low/high filter
  cv::Mat FileredImage;
  cv::addWeighted( lowFilteredImage, 1.0, highFilteredImage, 1.0, 0.0, FileredImage);

  return FileredImage;
}
