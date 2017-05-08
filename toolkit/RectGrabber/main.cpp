/*********************************************************************
 * MODULE: Rectangle Grabber
 *
 * PURPOSE: RectGrabber is for video labeling. Using your mouse
 * 		pointer rectangle the region, and this program will output
 *		the coordinate of the rectangle region (x, y, width, height)
 *		into the target file.
 *
 *		The output file contains 6 columns as following:
 *			frame#  x  y  width  height  object_name
 *		Each column is separated by a tab charactor '\t'.
 *		
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-08
 *********************************************************************/

#include "utils.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>

#include <stdio.h>

using namespace std;
using namespace cv;

char _video_src_[1024] = "";
char _output_dst_[1024] = "";
char _target_name_[1024] = "";
bool _trace_target_ = false;

int main(int argc, char **argv)
{
	parseArgs(argc, argv);

	VideoCapture video_stream(_video_src_);
	if( !video_stream.isOpened() )
	{
		printf("[main]: Cannot open video file %s\n", _video_src_);
		exit(1);
	}

	ofstream outfile(_output_dst_);
	vector<Rect> targets;
	int frame_counter = 1;

	// video frame
	Mat frame;
	video_stream.read(frame);

	// mouse event params
	MouseEventParam mouse_param;
	mouse_param.action_ = WAIT_NEXT;

	namedWindow("frame");
	moveWindow("frame", 25, 25);

	setMouseCallback("frame", mouseEvent, &mouse_param);

	while(1)
	{
		char ret = waitKey(15);

		if(ret == 27)
			break;

		Mat drawing_frame;
		frame.copyTo(drawing_frame);

		mouseActionReactor(mouse_param, drawing_frame, targets);

		switch(ret)
		{
			case 'n':
				video_stream.read(frame);
				writeTargets2file(outfile, targets, frame_counter++);
				break;
			case 'c':
				targets.clear();
				break;
			default:
				break;
		}

		for(int i = 0; i < targets.size(); i++)
			rectangle(drawing_frame, targets[i], Scalar(0, 255, 0), 2);

		imshow("frame", drawing_frame);
	}

	destroyWindow("frame");
	outfile.close();
	video_stream.release();

	return 0;
}