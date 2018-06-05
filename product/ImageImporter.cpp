
#include "ImageImporter.h"

#include <stdexcept>
#include <opencv2/highgui.hpp> 

#define BMP_FORMAT ".bmp"
#define JPG_FORMAT ".jpg"
#define PNG_FORMAT ".png"

ImageImporter::ImageImporter()
{

}

cv::Mat ImageImporter::getImage(const std::string& fileName)
{
  if( fileName.find(BMP_FORMAT) == std::string::npos &&
      fileName.find(JPG_FORMAT) == std::string::npos &&
      fileName.find(PNG_FORMAT) == std::string::npos )
  {
    throw std::invalid_argument("fileName fileExtension");
  }

  cv::Mat image = cv::imread(fileName,CV_LOAD_IMAGE_COLOR);
  if(image.data == NULL)
  {
    throw std::invalid_argument("fileName");
  }

  return image;
}