#include "GridCalculator.h"
#include <opencv2/imgproc.hpp>

//debug
#include <opencv2/highgui.hpp>

#define MORPH_OPERATOR_BLACKHAT     0x06
#define MORPH_ELEMENT_RECT          0x00
#define BLUR_AMOUNT_PX              0x03
#define LINE_DEGREES                0x02


GridCalculator::GridCalculator()
{
}


std::vector<Line> GridCalculator::Calculate(cv::Mat input_image, cv::Mat *output_image, int kernelSize, 
                                                         int blackWhiteThreshold, int lineThreshold)
{
    if(kernelSize < 1 || kernelSize > 25 )
    {
        throw std::out_of_range("kernelSize");
    }

    if(blackWhiteThreshold < 0 || blackWhiteThreshold > 255)
    {
        throw std::out_of_range("threshold");
    }

    if(input_image.data == NULL)
    {
        throw std::invalid_argument("input_image");
    }

    cv::Mat filteredImage           =  FilterImage(input_image,kernelSize,blackWhiteThreshold);
    //cv::imshow("test 1 ", filteredImage);
    std::vector<Line> lines         =  GenerateGrid(filteredImage,lineThreshold);

    if(output_image != NULL)
    {
        filteredImage               =  Plot(filteredImage, lines);
        *output_image = filteredImage;
    }

    return lines;
}

cv::Mat GridCalculator::FilterImage(cv::Mat image, int kernelSize, int blackwhiteThreshold)
{
    cv::Mat filteredImage;
    cv::Mat element = getStructuringElement(MORPH_ELEMENT_RECT, cv::Size(2 * kernelSize + 1, 2 * kernelSize + 1), 
                                            cv::Point(kernelSize, kernelSize));

	morphologyEx(image, filteredImage, MORPH_OPERATOR_BLACKHAT, element);

    //aangepast
    cv::cvtColor(filteredImage, filteredImage, CV_BGR2GRAY);

    std::vector<cv::Vec2f> lines;


    cv::medianBlur(filteredImage, filteredImage, BLUR_AMOUNT_PX);

	filteredImage = filteredImage > blackwhiteThreshold;

    cv::cvtColor(filteredImage, filteredImage, CV_GRAY2BGR);

    return filteredImage;    
}


std::vector<Line> GridCalculator::GenerateGrid(cv::Mat filteredImage, int lineThreshold)
{
    cv::Mat grayImage ;
    // dit veranderd =
    cv::cvtColor(filteredImage, grayImage, CV_HSV2RGB);
    cv::cvtColor(grayImage, grayImage, CV_RGB2GRAY);
   // cv::imshow("test 2 ", grayImage);

    std::vector<cv::Vec2f> l;
    cv::HoughLines(grayImage, l, 1, CV_PI / LINE_DEGREES, lineThreshold, 0, 0);

    return ConvertVect2fToLine(l);
}

std::vector<Line> GridCalculator::ConvertVect2fToLine(std::vector<cv::Vec2f> vects)
{
    std::vector<Line> lines;
    lines.clear();

    for (size_t i = 0; i < vects.size(); i++)
    {
        float rho = vects[i][0], theta = vects[i][1];
        Line line;
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		line.beginPoint.x   = cvRound(x0 + 2000 * (-b));
		line.beginPoint.y   = cvRound(y0 + 2000 * (a));
		line.endPoint.x     = cvRound(x0 - 2000 * (-b));
		line.endPoint.y     = cvRound(y0 - 2000 * (a));

        lines.push_back(line);
    }
    return lines;
}


cv::Mat GridCalculator::Plot(cv::Mat image, std::vector<Line>lines)
{
    cv::Mat im = image.clone();
    for (size_t i = 0; i < lines.size(); i++)
	{
        cv::Point bP = cv::Point(lines.at(i).beginPoint.x,lines.at(i).beginPoint.y);
        cv::Point eP = cv::Point(lines.at(i).endPoint.x,lines.at(i).endPoint.y);
        
		cv::line(im, bP, eP, cv::Scalar(10, 10, 50), 1, CV_AA);
	}
    return im;
}