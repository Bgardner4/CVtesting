#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include "Intro.h"

/*********************show image************************************
*******************************************************************/
int returnImage(char** argv) {
	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty()) return -1;
	cv::namedWindow("example", cv::WINDOW_AUTOSIZE);
	cv::imshow("example", img);
	cv::waitKey(0);
	cv::destroyWindow("example");
	return 0;
}

/************************smoothed image******************************
********************************************************************/
int returnSmoothedImage(char** argv) {
	cv::Mat image = cv::imread(argv[1], -1);

	//create windows to show input and output image
	cv::namedWindow("video in", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("video out", cv::WINDOW_AUTOSIZE);

	//show input image
	cv::imshow("video in", image);

	//create and out image
	cv::Mat out;

	//apply filter to input
	cv::GaussianBlur(image, out, cv::Size(5, 5), 3, 3);
	cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);

	//show smoothed image
	cv::imshow("video out", out);

	//wait for exit signal
	cv::waitKey(0);

	return 0;
}

/************************downsample image****************************
********************************************************************/
int returnSmallImage(char** argv) {
	cv::Mat img1, img2;

	cv::namedWindow("In", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Out", cv::WINDOW_AUTOSIZE);

	img1 = cv::imread(argv[1]);
	cv::imshow("In", img1);

	cv::pyrDown(img1, img2);
	cv::imshow("Out", img2);

	cv::waitKey(0);

	return 0;
}

/************************canny image****************************
********************************************************************/
int returnCannyImage(char** argv) {
	cv::Mat img_rgb, img_gry, img_cny;

	cv::namedWindow("grey", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("canny", cv::WINDOW_AUTOSIZE);

	img_rgb = cv::imread(argv[1]);

	cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);
	cv::imshow("grey", img_gry);

	cv::Canny(img_gry, img_cny, 10, 100, 3, true);
	cv::imshow("canny", img_cny);

	cv::waitKey(0);

	return 0;
}

/***********************show video***********************************
********************************************************************/

int returnVideo(char** argv) {
	cv::namedWindow("example", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;
	cap.open(std::string(argv[1]));

	cv::Mat frame;
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;
		cv::imshow("example", frame);
		if ((char)cv::waitKey(33) >= 0) break;
	}
	cv::destroyWindow("example");
	std::cout << "Done!";
	return 0;
}

/********************video camera***********************************
*******************************************************************/
int returnVideoInput(int argc, char** argv) {
	cv::VideoCapture cap;
	if (argc == 1) cap.open(0);
	else cap.open(argv[1]);

	if (!cap.isOpened()) {
		std::cerr << "Couldnt open capture." << std::endl;
		return -1;
	}

	cv::Mat frame;
	for (;;) {
		cap >> frame;
		if (frame.empty()) break;
		cv::imshow("example", frame);
		if ((char)cv::waitKey(33) >= 0) break;
	}
	cv::destroyWindow("example");
	std::cout << "Done!";
	return 0;
}

/*********************Video with slide bar*************************
******************************************************************/
int g_slider_position = 0;
int g_run = 1, g_dontset = 0;
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void*) {
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	if (!g_dontset) g_run = 1;
	g_dontset = 0;
}

int betterVideo(char** argv) {
	cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
	g_cap.open(argv[1]);

	int frames = (int)g_cap.get(CV_CAP_PROP_FRAME_COUNT);
	int tmpw = (int)g_cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	std::cout << "Video has " << frames << " frames and dimensions(" << tmpw << ", " << "tmph" << ")." << std::endl;

	cv::createTrackbar("Position", "video", &g_slider_position, frames, onTrackbarSlide);

	cv::Mat frame;
	for (;;) {
		if (frames != 0) {
			g_cap >> frame;
			if (frame.empty()) break;
			int current_pos = (int)g_cap.get(CV_CAP_PROP_POS_FRAMES);
			g_dontset = 0;

			cv::setTrackbarPos("Position", "video", current_pos);
			cv::imshow("video", frame);

			frames -= 1;
		}

		char c = (char)cv::waitKey(10);
		if (c == 's') {
			g_run = 1;
			std::cout << "Single step, run = " << g_run << std::endl;
		}
		else if (c == 'r') {
			g_run = -1;
			std::cout << "Run mode, run = " << g_run << std::endl;
		}
		else if (c == 27) break;
	}

	return 0;

}
