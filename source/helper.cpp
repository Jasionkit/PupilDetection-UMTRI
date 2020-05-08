#include "helper.hpp"
#include "findPupil.hpp"

vector<vector<int>> left_center;
vector<vector<int>> right_center;

int readInput(vector<int> &face_pts, string &outputName) {
    bool first = true;
    int total_frame = 0;
    ifstream fin;
    fin.open("inputs/" + outputName + "_Feature.csv");
    if (!fin.is_open()) {
        cout << "Error: Input file not open.\n";
        exit(1);
    }
    vector<string> row;
    string line, word;
    getline(fin, line);
    while (getline(fin, line)) {
        stringstream s(line);
        row.clear();
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        
        // Eye data
        if (stoi(row[5]) == 0 || stoi(row[6]) == 0 || stoi(row[7]) == 0 || stoi(row[8]) == 0) {
            left_center.push_back(left_center[total_frame-1]);
            right_center.push_back(left_center[total_frame - 1]);
        }
        else {
            vector<int> new_row;
            new_row.reserve(2);
            new_row.push_back(stoi(row[5]));
            new_row.push_back(stoi(row[6]));
            left_center.push_back(new_row);
            new_row.clear();
            new_row.push_back(stoi(row[7]));
            new_row.push_back(stoi(row[8]));
            right_center.push_back(new_row);
        }
        
        // Face data
        if (first) {
            face_pts.push_back(stoi(row[1]) - 25);
            face_pts.push_back(stoi(row[2]) - 25);
            face_pts.push_back(stoi(row[3]) - stoi(row[1]) + 25);
            face_pts.push_back(stoi(row[4]) - stoi(row[2]) + 25);
            first = false;
        }

        ++total_frame;
    }
    fin.close();
    return total_frame;
}

void getPupil(int frame_num, Mat &frame_gray, ofstream &outFile) {
    Rect leftEyeRegion(left_center[frame_num][0]-25, left_center[frame_num][1]-15, 50, 30);
    Rect rightEyeRegion(right_center[frame_num][0]-25, right_center[frame_num][1]-15, 50, 30);
    
    Point leftPupil = findPupilCenter(frame_gray, leftEyeRegion);
    Point rightPupil = findPupilCenter(frame_gray, rightEyeRegion);

    // Apply shift
    leftPupil.x += left_center[frame_num][0] - 25;
    leftPupil.y += left_center[frame_num][1] - 15;
    rightPupil.x += right_center[frame_num][0] - 25;
    rightPupil.y += right_center[frame_num][1] - 15;
    
    outFile << leftPupil.x << "," << leftPupil.y << "," << rightPupil.x << "," << rightPupil.y << ",";
    
    circle(frame_gray, rightPupil, 3, 1234);
    circle(frame_gray, leftPupil, 3, 1234);
}
