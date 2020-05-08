#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking/tracker.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include "findPupil.hpp"
#include "opticalFlow.hpp"
#include "helper.hpp"

using namespace std;
using namespace cv;

// Global variables

int main(int argc, const char** argv) {
    // Get user input info
    string subject, route_type, camera_type;
    cout << "Enter subject number (eg. MRXXX): ";
    cin >> subject;
    cout << "Route type - UN/UT/HN/HT: ";
    cin >> route_type;
    cout << "Webcam - Down/Front: ";
    cin >> camera_type;
    string output_name = subject + "_" + route_type + "_" + camera_type;
    
    // Read in data from file
    vector<int> face_pts;
    int total_frames = readInput(face_pts, output_name);
    Rect head = Rect(face_pts[0], face_pts[1], face_pts[2], face_pts[3]);
    
    // Set up output file
    ofstream outputFile;
    outputFile.open("data/" + output_name + "_Pupil.csv");
    if (!outputFile.is_open()) {
        cout << "Error: Output file not open.\n";
        exit(1);
    }
    outputFile << "Frame" << "," << "Left Pupil (x)" << "," << "Left Pupil (y)" << "," << "Right Pupil (x)" << "," << "Right Pupil (y)" << "," << "Tracking Pts Diff (x)" << "," << "Tracking Pts Diff (y)" << "\n";
    
    // Intialize video input
    VideoCapture capture("videos/" + output_name + ".avi");
    string main_window_name = "Frame Ouput";
    
    cout << total_frames << "\n";

    for (int i = 1; i <= total_frames; ++i) {
        Mat frame;
        int frame_num = capture.get(1);
        if (frame_num % 1800 == 0) {
            cout << frame_num / 1800 << "\n";
        }
        capture >> frame;
        outputFile << frame_num << ",";
        
        // Find pupil
        vector<Mat> rgbChannels(3);
        split(frame, rgbChannels);
        Mat frame_gray = rgbChannels[2];
        getPupil(frame_num, frame_gray, outputFile);
        
        // Perform Lunar-Kascade optical flow tracking
        setupTracking(frame, head);
        opticalFlowTracking(outputFile);
        
        // Display image
        imshow(main_window_name, frame_gray);

        // Wait keys
        int c = waitKey(10);
        if ((char)c == 'q') { break; }
        if ((char)c == 't') { cout << frame_num << "\n"; }
    }
    outputFile.close();
    return 0;
}

