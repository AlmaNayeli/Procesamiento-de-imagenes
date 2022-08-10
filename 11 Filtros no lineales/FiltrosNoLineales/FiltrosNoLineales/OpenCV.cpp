// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void filtroMinimo(Mat img_src, Mat* img_dst);
void filtroMaximo(Mat img_src, Mat* img_dst);
void filtroMediana(Mat img_src, Mat* img_dst);
int main()
{
    //Mat img = imread("lenacolor.png", IMREAD_GRAYSCALE);
    Mat img = imread("lenaRuido.jpg", IMREAD_GRAYSCALE);
    imshow("imagen", img);

    Mat img2(img.rows, img.cols, img.type());
    filtroMinimo(img, &img2);
    imshow("Img filtro minimo", img2);

    Mat img3(img.rows, img.cols, img.type());
    filtroMaximo(img, &img3);
    imshow("Img filtro maximo", img3);

    Mat img4(img.rows, img.cols, img.type());
    filtroMediana(img, &img4);
    imshow("Img filtro mediana", img4);

   

    waitKey(0);
    
}
void filtroMinimo(Mat img_src, Mat* img_dst)
{
    uchar vector[9];
    uchar* min;
    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            vector[0] = img_src.at<uchar>(i - 1, j - 1); 
            vector[1] = img_src.at<uchar>(i - 1, j); 
            vector[2] = img_src.at<uchar>(i - 1, j + 1);
            vector[3] = img_src.at<uchar>(i, j - 1);
            vector[4] = img_src.at<uchar>(i, j); 
            vector[5] = img_src.at<uchar>(i, j + 1);
            vector[6] = img_src.at<uchar>(i + 1, j - 1);
            vector[7] = img_src.at<uchar>(i + 1, j);
            vector[8] = img_src.at<uchar>(i + 1, j + 1);
            min=min_element(vector, vector+9);
            img_dst->at<uchar>(i, j) = *min;
        }
    }
}
void filtroMaximo(Mat img_src, Mat* img_dst)
{
    uchar vector[9];
    uchar* max;
    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            vector[0] = img_src.at<uchar>(i - 1, j - 1);
            vector[1] = img_src.at<uchar>(i - 1, j);
            vector[2] = img_src.at<uchar>(i - 1, j + 1);
            vector[3] = img_src.at<uchar>(i, j - 1);
            vector[4] = img_src.at<uchar>(i, j);
            vector[5] = img_src.at<uchar>(i, j + 1);
            vector[6] = img_src.at<uchar>(i + 1, j - 1);
            vector[7] = img_src.at<uchar>(i + 1, j);
            vector[8] = img_src.at<uchar>(i + 1, j + 1);
            max = max_element(vector, vector + 9);
            img_dst->at<uchar>(i, j) = *max;
        }
    }
}

uchar findMedian(uchar a[], int n)
{
    // First we sort the array 
    sort(a, a + n);

    // check for even case 
    if (n % 2 != 0)
        return a[n / 2];

    return (a[(n - 1) / 2] + a[n / 2]) / 2;
}
void filtroMediana(Mat img_src, Mat* img_dst)
{
    uchar vector[9];
    uchar mediana;
    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            vector[0] = img_src.at<uchar>(i - 1, j - 1);
            vector[1] = img_src.at<uchar>(i - 1, j);
            vector[2] = img_src.at<uchar>(i - 1, j + 1);
            vector[3] = img_src.at<uchar>(i, j - 1);
            vector[4] = img_src.at<uchar>(i, j);
            vector[5] = img_src.at<uchar>(i, j + 1);
            vector[6] = img_src.at<uchar>(i + 1, j - 1);
            vector[7] = img_src.at<uchar>(i + 1, j);
            vector[8] = img_src.at<uchar>(i + 1, j + 1);
            mediana = findMedian(vector, 9);
            img_dst->at<uchar>(i, j) = mediana;
        }
    }
}