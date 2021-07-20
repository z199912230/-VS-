#include "model.h"

//����ģ�彨��
void makeModel()
{
	//Mat src = imread("model.png", CV_LOAD_IMAGE_GRAYSCALE);
	//threshold(src, src, 100, 255, CV_THRESH_BINARY_INV);	// ��ֵ��
	Mat src = imread("model.png");//��ȡģ��
	paintGrey(src, src);//��ģ����лҶȻ�����
	//imshow("grey", src);
	towNum(src, src, 150, 255, 0);//��ֵ��
	//imshow("tow", src);//��ʾͼ��
	imwrite("tow.jpg", src);
	for (int i = 0; i <20; i++)
	{
		char fileName[21];
		Mat rImg, dst;
		cutLeft(src, dst, rImg);
		sprintf_s(fileName, "%d.png", i);//����0~19.png
		imwrite(fileName, dst);//
		src = rImg;
	}
}

// ��ֵ��
void towNum(Mat &src, Mat &dst, int thresh, int maxVul, bool flag)
{
	Mat tmp = Mat(src.size(), CV_8U);//��ȡ��С
	for (int i = 0; i < src.rows; i++)//��
	{
		for (int j = 0; j < src.cols; j++)//��
		{
			uchar num = src.at<uchar>(i, j);
			if (flag == 0)
			{
				if (num <= thresh)
					tmp.at<uchar>(i, j) = 255;
				else
					tmp.at<uchar>(i, j) = 0;
			}
			else
			{
				if (num <= thresh)
					tmp.at<uchar>(i, j) = 0;
				else
					tmp.at<uchar>(i, j) = 255;
			}
		}
	}
	dst = tmp;
}

// �Ҷ�ת��
void paintGrey(Mat &src, Mat &dst)
{
	Mat temp = Mat(src.size(), CV_8U);
	int row = src.rows;
	int col = src.cols;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			uchar b = src.at<Vec3b>(i, j)[0] * 0.144;
			uchar g = src.at<Vec3b>(i, j)[1] * 0.587;
			uchar r = src.at<Vec3b>(i, j)[2] * 0.299;
			temp.at<uchar>(i, j) = saturate_cast<uchar>(b + g + r);
			//��ֹ���
			if ((b + g + r) > 255)
				temp.at<uchar>(i, j) = 255;
			else
				temp.at<uchar>(i, j) = b + g + r;
		}
	}
	dst = temp;
}

//�е����ұ߿հ׺������и�//��
int cutLeft(Mat& src, Mat& leftImg, Mat& rightImg)
{
	int left, right;
	left = 0;
	right = src.cols;//����

	int i;
	for (i = 0; i < src.cols; i++)
	{
		int colValue = getColSum(src, i);
		if (colValue > 0)
		{
			left = i;
			break;
		}
	}
	if (left == 0)
		return 1;
	for (; i < src.cols; i++)
	{
		int colValue = getColSum(src, i);
		if (colValue == 0)
		{
			right = i;
			break;
		}
	}
	int width = right - left;
	Rect rect(left, 0, width, src.rows);
	leftImg = src(rect).clone();//

	Rect rectRight(right, 0, src.cols - right, src.rows);//��x��y���곤��
	rightImg = src(rectRight).clone();

	cutTop(leftImg, leftImg);
	return 0;
}

//ͳ�������еĶ�ֵ�ܺ�
int getColSum(Mat src, int col)  
{
	int sum = 0;
	int height = src.rows;
	int width = src.cols;
	for (int i = 0; i < height; i++)
	{
		sum = sum + src.at<uchar>(i, col);
	}
	return sum;
}

//�е�ͼƬ�����¿հ�
void cutTop(Mat& src, Mat& dstImg)  
{
	int top, bottom;
	top = 0;
	bottom = src.rows;

	int i;
	for (i = 0; i < src.rows; i++)
	{
		int colValue = getRowSum(src, i);
		if (colValue > 0)
		{
			top = i;//ͳ�Ƹ߶�
			break;
		}
	}
	for (; i < src.rows; i++)
	{
		int colValue = getRowSum(src, i);
		if (colValue == 0)
		{
			bottom = i;
			break;
		}
	}
	int height = bottom - top;
	Rect rect(0, top, src.cols, height);
	dstImg = src(rect).clone();
}

int getRowSum(Mat src, int row)//ͳ�������е��ܺ�
{
	int sum = 0;
	int height = src.rows;
	int width = src.cols;
	for (int i = 0; i < width; i++)
	{
		sum = sum + src.at<uchar>(row, i);
	}
	return sum;
}