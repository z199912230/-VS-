#include "model.h"
#include "picture.h"
extern Mat crop;
void getPXSum(Mat &src, int &a) //计算图像最小距离
{
	towNum(src, src, 150, 255, 1);
	a = 0;
	for (int i = 0; i < src.rows; i++)//行像素
	{
		for (int j = 0; j < src.cols; j++)//列像素
		{
			a += src.at<uchar>(i, j);//第i行第j列的的值.at()是一个返回值
		}
	}
}

// 求绝对值
void my_abs(Mat &src, Mat &dst, Mat &result)
{
	Mat tmp = Mat(src.size(), CV_8U);//无符号整数
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar a = src.at<uchar>(i, j);
			uchar b = dst.at<uchar>(i, j);
			tmp.at<uchar>(i, j) = a > b ? a - b : b - a;//如果a>b成立则a-b，否则b-a
		}
	}
	result = tmp;
}

int getSubtract(Mat &src, int TemplateNum)	//用于识别数字
{
	Mat img_result = Mat(src.size(), CV_8U);;
	int min = 1000000;
	int serieNum = 0;
	int serienum = 0;
	int num[20];
	for (int p = 0; p < 20; p++)
		num[p] = 0;
	for (int i = 0; i <= TemplateNum; i++)
	{
		char name[20];
		sprintf_s(name, "%d.png", i);
		Mat Template = imread(name);//读取图片文件
		paintGrey(Template, Template);//灰度转换
		//threshold(src, src, 100, 255, CV_THRESH_BINARY);
		towNum(Template, Template, 150, 255, 1);//二值化test模板
		towNum(src, src, 150, 255, 1);
		resize(src, src, Size(50, 50), 0, 0, CV_INTER_LINEAR);//缩放的大小为50*50，0，height/row,0，，双线性插值
		resize(Template, Template, Size(50, 50), 0, 0, CV_INTER_LINEAR);
		my_abs(Template, src, img_result);//结果保存到img_result
		int diff = 0;
		getPXSum(img_result, diff);//距离
		num[i] = diff;
			
		/*if (diff < min)
		{
			min = diff;
			serieNum = i;
			serienum = i;
			if (serienum >= 10)
				serienum =serienum -10;
		}*/
	}
	for (int i = 0; i < 20; i++)
	{
		int cin;
		cin >> num[i];

		if (num[i] < num[serieNum])
		{
			serieNum = i;
			serienum = i;
			if (serienum >= 10)
				serienum = serienum - 10;
		}
	}
	//cout << "最小距离是" << min << ",";
	cout << "最小距离是" << num [serienum] << ",";
	
		cout << "匹配的是第" << serieNum << "个模板，匹配的数字是" << serienum << endl;
	
	return serieNum;
}

int main()
{
	// 建模板
	makeModel();


	//用于识别
	Mat src = imread("test.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat test = getPicture();
	while (char(waitKey(0))!='q')//无返回值，必须有按键
	{
		imshow("test", test);//
		Mat leftImg, rightImg;
		int res = cutLeft(test, leftImg, rightImg);//切割
		while (res == 0)//切割完成后
		{
			Mat srcTmp = rightImg;
			getSubtract(leftImg, 19 );
			res = cutLeft(srcTmp, leftImg, rightImg);
		}
		
		while (char(waitKey(1)) != 13)
		{
		}
		paintGrey(crop, crop);
		imshow("crop", crop);
		towNum(crop, crop, 150, 255, 0);
		test = crop;
	}
	waitKey(0);
	return 0;
}

