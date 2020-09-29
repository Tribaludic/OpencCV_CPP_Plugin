#include "OpencvManager.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;

OpencvManager::OpencvManager()
{
    //rng = RNG(12345);        
    active = false;
}


Mat OpencvManager::redFilter(const Mat& src)
{
    Mat3b hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);

    Mat1b mask1, mask2;
    /*inRange(hsv, Scalar(0, 70, 50), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask2);*/

    inRange(hsv, Scalar(0, 100, 100), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(160, 100, 100), Scalar(179, 255, 255), mask2);

    Mat1b mask = mask1 | mask2;

    return mask;
}

int OpencvManager::Process(Color32* raw, int width, int height)
{
    int detection = -1;
    if (!active) {
        frame = Mat(height, width, CV_8UC4, raw);
        flip(frame, frame, +1);
        imshow("Simulator", frame);
        active = true;
    }
    else {
        Mat newframe = Mat(height, width, CV_8UC4, raw);
        frame = newframe;
        flip(frame, frame, +1);
        imshow("Simulator", frame);
    }


        Mat redOnly = redFilter(frame);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        /// Find contours
        findContours(redOnly, contours, hierarchy, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes
            ::CHAIN_APPROX_SIMPLE);

        if (contours.size() > 0) {
            detection = 1;

            /// Draw contours if exist
            Mat drawing = Mat::zeros(redOnly.size(), CV_8UC3);
            for (int i = 0; i < contours.size(); i++)
            {
                Scalar color = Scalar(0, 255, 0);
                drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
            }

            /// Show in a window
            //namedWindow("Contours", CV_WINDOW_AUTOSIZE);
            imshow("Contours", drawing);
        }

        //Show Image with red filter only
        imshow("Red Detection", redOnly);


        return detection;    

    //return 777;
}
