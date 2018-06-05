
#include "Camera.h"


Camera::Camera(int cameraNumber)
{
  if(cameraNumber < 0)
  {
    throw std::out_of_range("cameraNumber");
  }

  cv::VideoCapture cap(cameraNumber);
  CaptureDevice = cap;  

  if(!CaptureDevice.isOpened())
  {
    throw std::runtime_error("CaptureDevice");
  }

}


cv::Mat Camera::getImage()
{
  if(!CaptureDevice.isOpened())
  {
    throw std::runtime_error("CaptureDevice");
  }

  cv::Mat image;
  CaptureDevice >> image;
  return image;
}