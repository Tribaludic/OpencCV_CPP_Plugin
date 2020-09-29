#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Color32.h"

using namespace cv;



class OpencvManager
{
private:
	//RNG rng;
	Mat frame;
	bool active;

public:
	OpencvManager();
	int Process(Color32* raw, int width, int height);
	Mat redFilter(const Mat& src);
};

