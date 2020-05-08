#ifndef helper_hpp
#define helper_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

int readInput(vector<int> &face_pts, string &outputName);
void getPupil(int frame_num, cv::Mat &frame_gray, ofstream &outFile);

#endif /* helper_hpp */
