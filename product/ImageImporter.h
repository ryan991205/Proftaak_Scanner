
#ifndef IMAGEIMPORTER_H_
#define IMAGEIMPORTER_H_

#include <string>
#include <opencv2/core/core.hpp>


class ImageImporter
{
  private:

  public:

  ImageImporter();
  ~ImageImporter();

  cv::Mat getImage(const std::string& fileName);
};

#endif