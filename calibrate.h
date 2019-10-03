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

	//自定义函数
	bool addBoard(const cv::Mat& board);
	bool startCalibrating();
	bool fix(cv::Mat& image, cv::Mat& result);
	bool saveMatrix(std::string str);
	void loadMatrix(std::string str);
	bool isEnough();
	bool isLoaded();

private:
	int nBoard;//棋盘个数
	int boardN;//单个棋盘的关键点总数
	int boardW;//横向关键点数目
	int boardH;//纵向关键点数目
	cv::Size boardSize;//棋盘的关键点尺寸

	int savedBoardNum = 0;//保存的棋盘数
	std::vector<std::vector<cv::Point2f>> imagePoints;//关键点位于图像的位置
	std::vector<std::vector<cv::Point3f>> objectPoints;//关键点的坐标
	cv::Size imageSize;//图像像素大小

	bool isMatrixLoaded = false;//相机和畸变矩阵是否被计算或者被读取
	cv::Mat intrinsicMatrix;//相机矩阵
	cv::Mat distortionCoeffs;//畸变矩阵
	cv::Mat map1, map2;
};

