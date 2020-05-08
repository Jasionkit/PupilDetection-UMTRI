#include "opticalFlow.hpp"

Mat cur_frame, cur_gray, prev_gray;
vector<Point2f> p0, p1;
bool reset_pts = true;

void setupTracking(Mat &frame, Rect &head_pt) {
    cur_frame = Mat(frame, head_pt);
    if (reset_pts) {
        cvtColor(cur_frame, prev_gray, COLOR_BGR2GRAY);
        goodFeaturesToTrack(prev_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
        reset_pts = false;
    }
}

void opticalFlowTracking(ofstream &outFile) {
    cvtColor(cur_frame, cur_gray, COLOR_BGR2GRAY);
    vector<uchar> status;
    vector<float> err;
    TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
    calcOpticalFlowPyrLK(prev_gray, cur_gray, p0, p1, status, err, Size(15, 15), 2, criteria);
    vector<Point2f> good_new;
    double x_diff = 0;
    double y_diff = 0;
    for (int i = 0; i < p0.size(); ++i) {
        // Select good points
        if (status[i] == 1) {
            good_new.push_back(p1[i]);
            x_diff += (p1[i].x - p0[i].x);
            y_diff += (p1[i].y - p0[i].y);
        }
    }
    x_diff = x_diff / double(good_new.size());
    y_diff = y_diff / double(good_new.size());
    if (good_new.size() < 10) {
        reset_pts = true;
        return;
    }
    outFile << x_diff << "," << y_diff << "\n";
    prev_gray = cur_gray.clone();
    p0 = good_new;
}
