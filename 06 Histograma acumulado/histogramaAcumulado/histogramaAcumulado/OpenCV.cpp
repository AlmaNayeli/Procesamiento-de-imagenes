// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histograma(Mat img, Mat* imgHistograma, int* hist);
void histogramaAcumulado(Mat img, Mat* imgHistAcum, int* histAcum);

int main()
{
    Mat img = imread("antenaOK.jpg", IMREAD_GRAYSCALE);
    imshow("imagen", img);

    uchar* pfila;
    int hist[256] = { 0 };
    int histAcum[256] = { 0 };
    Mat imgHist,imgHistAcum;
    
    histograma(img, &imgHist, hist);
    histogramaAcumulado(img, &imgHistAcum, histAcum);
    printf("Histograma e Histograma acumulado\n");
    for (int i = 0; i <= 255; i++)
    {
        printf("Intensidad %d = %d---Acumulado = %d\n",i, hist[i],histAcum[i]);
    }
   
    imshow("histograma", imgHist);
    imshow("Histograma Acumulado", imgHistAcum);

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
void histogramaAcumulado(Mat img, Mat* imgHistAcum, int* histAcum)
{
    Mat imgHist;
    uchar* pfila;
    int hist[256] = { 0 };
    histograma(img, &imgHist, hist);
    for (int j = 0; j < 256; j++)
    {
        for (int i = 0; i <= j; i++)
        {
            histAcum[j] = histAcum[j] + hist[i];
        }

    }
    int* maxIntensidad = max_element(&histAcum[0], &histAcum[256]);
   
    imgHistAcum->create(256, 256, CV_8UC1);
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < histAcum[i] * 256 / (*maxIntensidad); j++)
        {
            pfila = imgHistAcum->ptr<uchar>(imgHistAcum->rows - j - 1);
            pfila[i] = i;
        }
    }
}
