#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

void paintGrey(Mat &src, Mat &dst);
void towNum(Mat &src, Mat &dst, int thresh, int maxVul, bool flag = 0);
void makeModel();
int cutLeft(Mat& src, Mat& leftImg, Mat& rightImg);
int getColSum(Mat src, int col);
void cutTop(Mat& src, Mat& dstImg);
int getRowSum(Mat src, int row);