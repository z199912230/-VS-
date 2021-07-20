#include "picture.h"
#include "opencv.hpp"
#include <iostream>
using  namespace std;
using namespace cv;
// ȫ�ֱ���
// ��갴����־
bool ldown = false, lup = false;
// ԭʼͼ��
Mat src;
// ������ʼ����յ�����
Point corner1, corner2;
// ����Ȥ����
Rect box;
// ���к��ͼ
Mat crop;
// �ɼ�ͼ��
Mat getPicture()
{
	
	int c;
	
	VideoCapture capture("��http://�˺ţ�����@������IP���˿ںš�");//��������ͷ
	while (true)
	{
		capture.read(src);
		imshow("origion", src);
		c = waitKey(30);//��ʱ
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
		c = waitKey(30);//��ʱ
		if (c == 13)
		{
			v.release();
			break;
		}
	}*/
	//imshow("test", src);
	//src = imread("test.png");
	imshow("t", src);
	// ��������¼��ص�����
	setMouseCallback("t", mouse_callback);	
	while (char(waitKey(1)) != 13)
	{
	}
	paintGrey(crop, crop);
	towNum(crop, crop, 150, 255, 0);
	return crop;
}

// ����¼��ص�����
void mouse_callback(int event, int x, int y, int, void*)
{
	// ������������ʱ����¼��״̬������
	if (event == EVENT_LBUTTONDOWN)
	{
		ldown = true;
		corner1.x = x;
		corner1.y = y;
		cout << "Corner 1 recorded at" << corner1 << endl;
	}

	// ���������ſ�ʱ����¼��״̬������
	if (event == EVENT_LBUTTONUP)
	{
		// �ж�ѡȡ�������Ƿ����20������
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

	//���ƶ����ʱ�� ����ѡ������ �����ƾ���ѡ������ͼ��
	if (ldown == true && lup == false)
	{
		Point pt;
		pt.x = x;
		pt.y = y;
		Mat local_img = src.clone();
		rectangle(local_img, corner1, pt, Scalar(0, 0, 255));
		imshow("t", local_img);
		

	}

	// �������Ȥ���򣬲���ԭͼ���м���
	if (ldown == true && lup == true)
	{
		box.width = abs(corner1.x - corner2.x);
		box.height = abs(corner1.y - corner2.y);
		box.x = min(corner1.x, corner2.x);
		box.y = min(corner1.y, corner2.y);

		// ��ԭͼ���м��ã� ������ͼ
		crop = 0;
		crop = src(box);
		namedWindow("Crop", CV_WINDOW_AUTOSIZE);
		imshow("Crop", crop);
		ldown = false;
		lup = false;
		imshow("t", src);
	}
}
