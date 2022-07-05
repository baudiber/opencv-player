#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int, char**)
{
    Mat frame;
    VideoCapture video;
    video.open("/home/wm/jellyfish.mp4",CAP_ANY);
    // video.open("/home/wm/jellyfish.mp4",CAP_ANY,
    // {
    //     CAP_PROP_HW_ACCELERATION, VIDEO_ACCELERATION_VAAPI,
    // });
    double fps = video.get(CAP_PROP_FPS);
    cv::namedWindow("player", WINDOW_NORMAL);
    setWindowProperty("player", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	cout << "Frames per second using video.get(CAP_PROP_FPS) : " << fps << endl;
    // check if we succeeded
    if (!video.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        video.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        cv::resize(frame, frame, Size(2560, 1440), INTER_LINEAR);
        imshow("player", frame);
        // if (waitKey((1.0 / fps) * 1000) >= 0)
        if (waitKey(1) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
