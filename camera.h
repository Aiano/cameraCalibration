#pragma once
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

class Camera
{
public:
	Camera(int cameraIndex = 0);//构造函数
	~Camera();//析构函数

	//以下为自定义函数
	cv::Mat get_frame();//获取当前帧
	cv::Mat get_spun_frame(int angle = 0);//获取旋转后的当前帧
	int get_delay();//获取每帧之间的延迟
	

private:
	cv::VideoCapture cap;
	cv::Mat frame;
	cv::Mat spunFrame;
	double fps;
	int delay;
};

