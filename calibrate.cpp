#include "calibrate.h"

Calibrate::Calibrate(int numberOfBoard,int widthOfBoard,int heightOfBoard)
{
	nBoard = numberOfBoard;
	boardW = widthOfBoard;
	boardH = heightOfBoard;
	boardSize = cv::Size(boardW, boardH);
	boardN = boardH * boardW;
}

Calibrate::~Calibrate()
{
}

bool Calibrate::addBoard(const cv::Mat& board)
{
	if (savedBoardNum < nBoard) {
		imageSize = board.size();
		cv::Mat image = cv::Mat(board);//复制
		
		//寻找角点
		std::vector<cv::Point2f> corners;
		bool found = cv::findChessboardCorners(board, boardSize, corners);
		
		cv::drawChessboardCorners(image, boardSize, corners, found);

		//如果图像符合要求,则保存
		if (found) {
			imagePoints.push_back(corners);

			std::vector<cv::Point3f> opt;
			opt.resize(boardN);
			for (int j = 0; j < boardN; j++) {
				opt[j] = cv::Point3f((float)(j / boardW), (float)(j % boardH), 0.f);
			}
			objectPoints.push_back(opt);
			savedBoardNum++;//保存数加一
			cv::putText(image, "Image: " + std::to_string(savedBoardNum), cv::Point(20, 40), cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(255, 255, 255));
			cv::imshow("Image", image);
			cv::waitKey(0);
			cv::destroyWindow("Image");
		}
		return found;
	}
	else {
		std::clog << "Saved boards is enough." << std::endl;
		return false;
	}
	
}

bool Calibrate::startCalibrating()
{
	if (savedBoardNum == nBoard) {
		double err = cv::calibrateCamera(
			objectPoints,
			imagePoints,
			imageSize,
			intrinsicMatrix,
			distortionCoeffs,
			cv::noArray(),
			cv::noArray(),
			cv::CALIB_ZERO_TANGENT_DIST|cv::CALIB_FIX_PRINCIPAL_POINT
		);

		//消畸函数
		cv::initUndistortRectifyMap(
			intrinsicMatrix,
			distortionCoeffs,
			cv::Mat(),
			cv::noArray(),
			imageSize,
			CV_16SC2,
			map1,
			map2
		);
		isMatrixLoaded = true;
		std::clog << "Calibration done." << std::endl;
		return true;
	}
	else {
		std::cerr << "The board(s) aren't enough" << std::endl;
		return false;
	}
	
}

bool Calibrate::fix(cv::Mat& image,cv::Mat& result)
{
	if (isMatrixLoaded) {
		if (image.empty()) {
			std::cerr << "The image is empty" << std::endl;
			return false;
		}
		cv::remap(image, result, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
		return true;
	}
	else {
		std::cerr << "The matrix is unloaded." << std::endl;
		return false;
	}
	

}

bool Calibrate::saveMatrix(std::string str)
{
	if (isMatrixLoaded) {
		cv::FileStorage fs(str, cv::FileStorage::WRITE);
		fs << "imageSize" << imageSize;
		fs << "intrinsicMatrix" << intrinsicMatrix;
		fs << "distortionCoeffs" << distortionCoeffs;
		fs.release();
		std::clog << "Save successfully." << std::endl;
	}
	else {
		std::cerr << "The matrix is unloaded." << std::endl;
		return false;
	}
}

void Calibrate::loadMatrix(std::string str)
{
	cv::FileStorage fs(str, cv::FileStorage::READ);
	fs["imageSize"] >> imageSize;
	fs["intrinsicMatrix"] >> intrinsicMatrix;
	fs["distortionCoeffs"] >> distortionCoeffs;
	fs.release();
	std::cout << "Image Size:" << imageSize.width << " x " << imageSize.height << std::endl;
	cv::initUndistortRectifyMap(
		intrinsicMatrix,
		distortionCoeffs,
		cv::Mat(),
		cv::noArray(),
		imageSize,
		CV_16SC2,
		map1,
		map2
	);
	isMatrixLoaded = true;
	std::clog << "Matrix is loaded." << std::endl;
}

bool Calibrate::isEnough()
{
	return (savedBoardNum==nBoard);
}

bool Calibrate::isLoaded()
{
	return isMatrixLoaded;
}


