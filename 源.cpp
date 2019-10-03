#include <opencv2/opencv.hpp>
#include <iostream>
#include "camera.h"
#include "calibrate.h"

using namespace cv;
using namespace std;

int N_BOARD = 10;


int main()
{
	Camera cam(1);
	Calibrate calib(N_BOARD, 7, 7);

	Mat frame,fixedFrame;
	while (1) {
		frame=cam.get_frame();
		imshow("Camera", frame);

		char ch = waitKey(cam.get_delay());
		if (ch == 27) break;
		else if (ch == 'a') {
			bool isSucceed = calib.addBoard(frame);
			if (isSucceed) clog << "The board has been saved successfully." << endl;
			else clog << "The board couldn't be saved." << endl;
		}
		else if (ch == 'c' && calib.isEnough()) calib.startCalibrating();
		else if (ch == 'r' && calib.isLoaded()) {
			calib.fix(frame, fixedFrame);
			imshow("Fixed", fixedFrame);
			waitKey(0);
			destroyWindow("Fixed");
		}
		else if (ch == 's') calib.saveMatrix("intrinsics.xml");
		else if (ch == 'l') calib.loadMatrix("intrinsics.xml");
	}
	return 0;
}