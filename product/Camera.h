
#ifndef CAMERA_H_
#define CAMERA_H_

#include <stdexcept>
#include <opencv2/core.hpp>           // data structures and arithmetic routines.
#include <opencv2/videoio.hpp>

class Camera
{
  private:
  cv::VideoCapture CaptureDevice;

  public:
  Camera(int cameraNumber);

  cv::Mat getImage();
};

#endif