#pragma once
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

class Camera
{
public:
	Camera(int cameraIndex = 0);//���캯��
	~Camera();//��������

	//����Ϊ�Զ��庯��
	cv::Mat get_frame();//��ȡ��ǰ֡
	cv::Mat get_spun_frame(int angle = 0);//��ȡ��ת��ĵ�ǰ֡
	int get_delay();//��ȡÿ֮֡����ӳ�
	

private:
	cv::VideoCapture cap;
	cv::Mat frame;
	cv::Mat spunFrame;
	double fps;
	int delay;
};

