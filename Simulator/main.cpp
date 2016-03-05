/*
#include "irrlicht/irrlicht.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace cv;
*/
#include "Sim.h"
#include <opencv2/opencv.hpp>
int main()
{
    cv::Mat *f = new cv::Mat(640, 480,CV_8UC3);
    Sim sim (f);
    sim.start();
    delete (f);
    return 0;
}

/*
That's it. Compile and run.
**/
