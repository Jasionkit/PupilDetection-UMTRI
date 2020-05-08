#ifndef opticalFlow_hpp
#define opticalFlow_hpp

#include <stdio.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking/tracker.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

void setupTracking(Mat &frame, Rect &head_pt);
void opticalFlowTracking(ofstream &outFile);


#endif /* opticalFlow_hpp */
