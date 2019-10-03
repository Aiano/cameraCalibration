#pragma once
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

class Calibrate
{
public:
	Calibrate(int numberOfBoard, int widthOfBoard, int heightOfBoard);
	~Calibrate();

	//�Զ��庯��
	bool addBoard(const cv::Mat& board);
	bool startCalibrating();
	bool fix(cv::Mat& image, cv::Mat& result);
	bool saveMatrix(std::string str);
	void loadMatrix(std::string str);
	bool isEnough();
	bool isLoaded();

private:
	int nBoard;//���̸���
	int boardN;//�������̵Ĺؼ�������
	int boardW;//����ؼ�����Ŀ
	int boardH;//����ؼ�����Ŀ
	cv::Size boardSize;//���̵Ĺؼ���ߴ�

	int savedBoardNum = 0;//�����������
	std::vector<std::vector<cv::Point2f>> imagePoints;//�ؼ���λ��ͼ���λ��
	std::vector<std::vector<cv::Point3f>> objectPoints;//�ؼ��������
	cv::Size imageSize;//ͼ�����ش�С

	bool isMatrixLoaded = false;//����ͻ�������Ƿ񱻼�����߱���ȡ
	cv::Mat intrinsicMatrix;//�������
	cv::Mat distortionCoeffs;//�������
	cv::Mat map1, map2;
};

