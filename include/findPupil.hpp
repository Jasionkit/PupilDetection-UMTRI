// Credits to Tristan Hume's eyeLike software and Fabian Timm's Algorithm

#ifndef findPupil_hpp
#define findPupil_hpp

#include <stdio.h>

// Funcions
cv::Point findPupilCenter(cv::Mat &face, cv::Rect &eye);
cv::Point unscalePoint(cv::Point p, cv::Rect origSize);
void scaleToFastSize(const cv::Mat &src,cv::Mat &dst);
cv::Mat computeMatXGradient(const cv::Mat &mat);
void testPossibleCentersFormula(int x, int y, const cv::Mat &weight,double gx, double gy, cv::Mat &out);
bool floodShouldPushPoint(const cv::Point &np, const cv::Mat &mat);
cv::Mat floodKillEdges(cv::Mat &mat);
bool rectInImage(cv::Rect rect, cv::Mat image);
bool inMat(cv::Point p,int rows,int cols);
cv::Mat matrixMagnitude(const cv::Mat &matX, const cv::Mat &matY);
double computeDynamicThreshold(const cv::Mat &mat, double stdDevFactor);

#endif /* findPupil_hpp */
