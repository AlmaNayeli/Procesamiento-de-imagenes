// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histograma(Mat img, Mat* imgHistograma, int* hist);
void adaptacionContraste(Mat img_src, Mat* img_dst);
int main()
{
    Mat img = imread("caballo.jpg",IMREAD_GRAYSCALE);
    Mat imgHistograma;
    int hist[256] = { 0 };
    histograma(img, &imgHistograma, hist);
    imshow("imagen", img);
    imshow("histograma", imgHistograma);

    Mat img2(img.rows, img.cols, img.type());
    Mat imgHistograma2;
    int hist2[256] = { 0 };
    adaptacionContraste(img, &img2);
    histograma(img2, &imgHistograma2, hist2);
    
    imshow("imagen mejorada", img2);
    imshow("histograma de imagen mejorada", imgHistograma2);
    for (int i = 0; i < 256; i++)
    {
        printf("original intensidad %d= %d     nueva intensidad %d= %d\n", i,hist[i],i, hist2[i]);
    }

    imwrite("antenaBajoContraste.jpg", img2);
    waitKey(0);
    
}
void histograma(Mat img, Mat* imgHistograma, int* hist)
{
    uchar* pfila;
    for (int i = 0; i < img.rows; i++)
    {
        pfila = img.ptr<uchar>(i);
        for (int j = 0; j < img.cols; j++)
        {
            hist[pfila[j]]++;
        }
    }

    int* maxIntensidad = max_element(&hist[0], &hist[255]);
    imgHistograma->create(256, 256, CV_8UC1);

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < hist[i] * 256 / (*maxIntensidad); j++)
        {
            pfila = imgHistograma->ptr<uchar>(imgHistograma->rows - j - 1);
            pfila[i] = i;
        }
    }
}
void adaptacionContraste(Mat img_src, Mat* img_dst)
{
    const int pMin = 0, pMax = 255;
    int pHigh = 255, pLow = 0;
    Mat imgHistograma;
    int hist[256] = { 0 };
    uchar* pfila_src, * pfila_dst;
    histograma(img_src, &imgHistograma, hist);
    for (int i = 0; i < 256; i++)
    {
        if (hist[i] != 0)
        {
            pLow = i;
            break;
        }
    }
    for (int i = 255; i >= 0; i--)
    {
        if (hist[i] != 0)
        {
            pHigh = i;
            break;
        }
    }
    printf("\n pLow= %d\n", pLow);
    printf("\n pHigh= %d\n", pHigh);
    for (int i = 0; i < img_src.rows; i++)
    {
        pfila_src = img_src.ptr<uchar>(i);
        pfila_dst = img_dst->ptr<uchar>(i);
        for (int j = 0; j < img_src.cols; j++)
            pfila_dst[j] = ((pfila_src[j] - pLow) * (pMax - pMin) / (pHigh - pLow)) + pMin;        
    }
}