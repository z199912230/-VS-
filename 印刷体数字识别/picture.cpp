#include "picture.h"
#include "opencv.hpp"
#include <iostream>
using  namespace std;
using namespace cv;
// 全局变量
// 鼠标按键标志
bool ldown = false, lup = false;
// 原始图像
Mat src;
// 矩形起始点和终点坐标
Point corner1, corner2;
// 感兴趣区域
Rect box;
// 剪切后的图
Mat crop;
// 采集图像
Mat getPicture()
{
	
	int c;
	
	VideoCapture capture("“http://账号：密码@广域网IP：端口号”");//调用摄像头
	while (true)
	{
		capture.read(src);
		imshow("origion", src);
		c = waitKey(30);//延时
		if (c == 13)
		{
			capture.release();
			break;
		}
	}
	/*VideoCapture v(0);
	int c;
	while (v.read(src))
	{
		imshow("origin", src);
		c = waitKey(30);//延时
		if (c == 13)
		{
			v.release();
			break;
		}
	}*/
	//imshow("test", src);
	//src = imread("test.png");
	imshow("t", src);
	// 设置鼠标事件回调函数
	setMouseCallback("t", mouse_callback);	
	while (char(waitKey(1)) != 13)
	{
	}
	paintGrey(crop, crop);
	towNum(crop, crop, 150, 255, 0);
	return crop;
}

// 鼠标事件回调函数
void mouse_callback(int event, int x, int y, int, void*)
{
	// 当鼠标左键按下时，记录其状态和坐标
	if (event == EVENT_LBUTTONDOWN)
	{
		ldown = true;
		corner1.x = x;
		corner1.y = y;
		cout << "Corner 1 recorded at" << corner1 << endl;
	}

	// 当鼠标左键放开时，记录其状态和坐标
	if (event == EVENT_LBUTTONUP)
	{
		// 判断选取的区域是否大于20个像素
		if (abs(x - corner1.x) > 20 && abs(y - corner1.y) >20)
		{
			lup = true;
			corner2.x = x;
			corner2.y = y;
			cout << "Corner 2 recorded at" << corner2 << endl << endl;
		}
		else
		{
			cout << "Please select a bigger region" << endl;
			ldown = false;
		}
	}

	//当移动鼠标时， 更新选择区域， 并绘制矩形选择区域图形
	if (ldown == true && lup == false)
	{
		Point pt;
		pt.x = x;
		pt.y = y;
		Mat local_img = src.clone();
		rectangle(local_img, corner1, pt, Scalar(0, 0, 255));
		imshow("t", local_img);
		

	}

	// 定义感兴趣区域，并对原图进行剪裁
	if (ldown == true && lup == true)
	{
		box.width = abs(corner1.x - corner2.x);
		box.height = abs(corner1.y - corner2.y);
		box.x = min(corner1.x, corner2.x);
		box.y = min(corner1.y, corner2.y);

		// 对原图进行剪裁， 生成新图
		crop = 0;
		crop = src(box);
		namedWindow("Crop", CV_WINDOW_AUTOSIZE);
		imshow("Crop", crop);
		ldown = false;
		lup = false;
		imshow("t", src);
	}
}
