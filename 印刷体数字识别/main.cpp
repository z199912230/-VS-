#include "model.h"
#include "picture.h"
extern Mat crop;
void getPXSum(Mat &src, int &a) //����ͼ����С����
{
	towNum(src, src, 150, 255, 1);
	a = 0;
	for (int i = 0; i < src.rows; i++)//������
	{
		for (int j = 0; j < src.cols; j++)//������
		{
			a += src.at<uchar>(i, j);//��i�е�j�еĵ�ֵ.at()��һ������ֵ
		}
	}
}

// �����ֵ
void my_abs(Mat &src, Mat &dst, Mat &result)
{
	Mat tmp = Mat(src.size(), CV_8U);//�޷�������
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			uchar a = src.at<uchar>(i, j);
			uchar b = dst.at<uchar>(i, j);
			tmp.at<uchar>(i, j) = a > b ? a - b : b - a;//���a>b������a-b������b-a
		}
	}
	result = tmp;
}

int getSubtract(Mat &src, int TemplateNum)	//����ʶ������
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
		Mat Template = imread(name);//��ȡͼƬ�ļ�
		paintGrey(Template, Template);//�Ҷ�ת��
		//threshold(src, src, 100, 255, CV_THRESH_BINARY);
		towNum(Template, Template, 150, 255, 1);//��ֵ��testģ��
		towNum(src, src, 150, 255, 1);
		resize(src, src, Size(50, 50), 0, 0, CV_INTER_LINEAR);//���ŵĴ�СΪ50*50��0��height/row,0����˫���Բ�ֵ
		resize(Template, Template, Size(50, 50), 0, 0, CV_INTER_LINEAR);
		my_abs(Template, src, img_result);//������浽img_result
		int diff = 0;
		getPXSum(img_result, diff);//����
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
	//cout << "��С������" << min << ",";
	cout << "��С������" << num [serienum] << ",";
	
		cout << "ƥ����ǵ�" << serieNum << "��ģ�壬ƥ���������" << serienum << endl;
	
	return serieNum;
}

int main()
{
	// ��ģ��
	makeModel();


	//����ʶ��
	Mat src = imread("test.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat test = getPicture();
	while (char(waitKey(0))!='q')//�޷���ֵ�������а���
	{
		imshow("test", test);//
		Mat leftImg, rightImg;
		int res = cutLeft(test, leftImg, rightImg);//�и�
		while (res == 0)//�и���ɺ�
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

