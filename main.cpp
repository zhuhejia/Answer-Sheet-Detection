#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main() {
	Mat img = imread("/root/projects/detect_paper_lines/paper.jpg");
	if (img.empty()) { cout << "img is empty" << endl; }
	Mat img2 = imread("/root/projects/detect_paper_lines/paper.jpg", IMREAD_GRAYSCALE);
	if (img2.empty()) { cout << "img2 is empty" << endl; }
	threshold(img2, img2, 110, 255, THRESH_BINARY_INV);
	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(30, 1));
	morphologyEx(img2, img2, MORPH_OPEN, kernel1);
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat img3;
	morphologyEx(img2, img3, MORPH_DILATE, kernel2);
	vector<Vec4i> lines;
	HoughLinesP(img3, lines, 1, CV_PI / 500, 20, 50, 0);
	for (int i = 0; i < lines.size(); i++) {
		cout << i;
		Point point1(lines[i][0], lines[i][1]);
		Point point2(lines[i][2], lines[i][3]);
		line(img, point1, point2, Scalar(0, 0, 255), 3);
	}

	imshow("lines_morphology", img3);
	imshow("lines", img);
	waitKey(0);
	return 0;


}