﻿#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//------------------------------------------------------------------------
//从白天和黑天两组图片中获得白天和黑天的背景
//------------------------------------------------------------------------
//【OpenCV应用笔记】(彩色/灰度)图像像素值读取并保存到txt文件:http://www.cnblogs.com/skyseraph/archive/2012/02/23/2365542.html
//opencv中的IplImage http://blog.csdn.net/fenggaoyuehei/article/details/6040911
//1-23 15:53 所有图片叠加求背景法尝试，现在正在运行中...Git
//发现越弄越黑：存成图片会把double类型的只取0~255结果,于是在外面建立变量存储叠加的像素值
class Pixel
{
public:
	double v[3];
	Pixel(){v[0]=v[1]=v[2]=0;}
};
void getBg(int nPicNum=1)
{
	char name[100];
	IplImage* img;
	CvScalar p1;
	
	IplImage* des=cvLoadImage("Tao1/1.jpg",-1);
	Pixel *pixel=new Pixel[des->width*des->height];
	memset(pixel,0,sizeof(pixel));

	for(int k=2;k<=nPicNum;k++)
	{
		sprintf(name,"Tao1/%d.jpg",k);
		img=cvLoadImage(name,-1);
		//cout<<"图像的宽和高： "<<img->width<<" "<<img->height<<'\n';
		
		for(int i=0;i<img->height;i++)
		{
			for(int j=0;j<img->width;j++)
			{
				p1 = cvGet2D(img,i,j);
				pixel[i*img->width+j].v[0]+=p1.val[0];
				pixel[i*img->width+j].v[1]+=p1.val[1];
				pixel[i*img->width+j].v[2]+=p1.val[2];
			}    
		}
		cvReleaseImage(&img);
		/*cout<<k<<'\n';*/
	}
	for(int i=0;i<des->height;i++)
	{
		for(int j=0;j<des->width;j++)
		{
			p1 = cvGet2D(des,i,j);
			pixel[i*des->width+j].v[0]+=p1.val[0];
			pixel[i*des->width+j].v[1]+=p1.val[1];
			pixel[i*des->width+j].v[2]+=p1.val[2];
			p1.val[0]=pixel[i*des->width+j].v[0]/nPicNum;
			p1.val[1]=pixel[i*des->width+j].v[1]/nPicNum;
			p1.val[2]=pixel[i*des->width+j].v[2]/nPicNum;
			cvSet2D(des,i,j,p1);
			//cout<<p.val[0] <<" "<<p.val[1]<<" "<<p.val[2] <<" "<<endl;
		}    
	}
	sprintf(name,"Bg1/%d.jpg",nPicNum);
	cvSaveImage(name,des);
	/*cvShowImage("des",des);*/
	cvReleaseImage(&des);
	delete[] pixel;
}
int main()
{
	//int i=9;//(1\2\3\4\5\6\7\8\9

	//Mat src = imread("tao1/1.jpg",0);//读取图片到mat
	//Mat temp,dst;//src-->temp-->dst(src为原图；temp是src经canny提取边缘的图，
	////用于下面霍夫变换；dst是最终结果图，要在temp灰度图的基础上变为彩色图才能呈现画线效果）
	//Canny(src, temp, 10, 140, 3);//提取边缘(如果不边缘提取就会浪费巨大时间）
	//Mat src1;//放缩之后的
	////resize(src,src1,Size(800,600));  
	//
	//
	//
	//   //cvtColor(temp, dst, CV_GRAY2BGR);//将边缘提取的灰度图转换为BGR图便于画线
	//
	//imshow("src1",src);
	//waitKey();
	for(int i=28;i<67;i++)
	{
		getBg(i);
		cout<<i<<'\n';
	}
	waitKey();
}