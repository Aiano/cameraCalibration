#include "camera.h"

Camera::Camera(int cameraIndex)
{
	cap.open(cameraIndex);
	if (!cap.isOpened()) return;
	fps = cap.get(cv::CAP_PROP_FPS);
	std::clog << "The fps is " << fps << std::endl;
	delay = 1000 / fps;
}

Camera::~Camera()
{
	cap.release();
	std::clog << "The capture had been released." << std::endl;
}

cv::Mat Camera::get_frame()
{
	cap >> frame;
	return frame;
}

cv::Mat Camera::get_spun_frame(int angle)
{
	cap >> frame;
	cv::Mat rotMat = cv::getRotationMatrix2D(cv::Point(frame.cols / 2, frame.rows / 2), angle, 1.0);
	cv::warpAffine(frame, frame, rotMat, cv::Size(frame.cols, frame.rows));
	return frame;
}

int Camera::get_delay()
{
	return delay;
}
