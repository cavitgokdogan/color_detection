#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture vid(0);
	Mat frame;

	if (!vid.isOpened())
	{
		cout << "webcam failed to load" << endl;
		system("Pause");
		return -1;
	}
	namedWindow("control", CV_WINDOW_AUTOSIZE);

	int Hmindeg = 0;
	int Hmaxdeg = 179;

	int Smindeg = 192;
	int Smaxdeg = 255;

	int Vmindeg = 90;
	int Vmaxdeg = 255;

	createTrackbar("minH", "control", &Hmindeg, 179);
	createTrackbar("maxH", "control", &Hmaxdeg, 179);

	createTrackbar("minS", "control", &Smindeg, 255);
	createTrackbar("maxS", "control", &Smaxdeg, 255);

	createTrackbar("minV", "control", &Vmindeg, 255);
	createTrackbar("maxV", "control", &Vmaxdeg, 255);
										
	while (true)
	{

		bool bSuccess = vid.read(frame);  
		if (!bSuccess)
		{
			cout << "Could not load new frame" << endl;
			system("Pause");
			break;
		}

		Mat HSVres;
		cvtColor(frame, HSVres, COLOR_BGR2HSV);	
														
		Mat isres;

		inRange(HSVres, Scalar(Hmindeg, Smindeg, Vmindeg), Scalar(Hmaxdeg, Smaxdeg, Vmaxdeg), isres);   

		erode(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));	

		dilate(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(isres, isres, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));		       

		imshow("Black and white", isres);
		imshow("Original", frame);

		if (waitKey(30) == 27)
		{
			cout << "User exited with esc" << endl;
			break;
		}
	}

	return 0;
}
