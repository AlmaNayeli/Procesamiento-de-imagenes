// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ecualizar(Mat img, Mat* imgEcu);
void histograma(Mat img, Mat* imgHistograma, int* hist);
void histogramaAcumulado(Mat img, Mat* imgHistAcum, int* histAcum);
int main()
{
    Mat img = imread("caballo2.jpg", IMREAD_GRAYSCALE);
    Mat img_Hist, img_HistAcum;
    int hist_img[256] = { 0 };
    int histAcum_img[256] = { 0 };
    histograma(img, &img_Hist, hist_img);
    histogramaAcumulado(img, &img_HistAcum, histAcum_img);
    imshow("imagen", img);
    imshow("histograma img", img_Hist);
    imshow("histograma acumulado img", img_HistAcum);

    Mat imgEcu(img.rows, img.cols, img.type());
    ecualizar(img, &imgEcu);
    Mat imgEcu_Hist, imgEcu_HistAcum;
    int hist_imgEcu[256] = { 0 }; 
    int histAcum_imgEcu[256] = { 0 };
    histograma(imgEcu, &imgEcu_Hist, hist_imgEcu);
    histogramaAcumulado(imgEcu, &imgEcu_HistAcum, histAcum_imgEcu);
    imshow("imagen ecualizada", imgEcu);
    imshow("histograma de img ecualizada", imgEcu_Hist);
    imshow("histograma acumulado de img ecualizada", imgEcu_HistAcum);


    waitKey(0);
    
}
void ecualizar(Mat img, Mat* imgEcu)
{
    uchar* pfila_img, * pfila_imgEcu;
    Mat imgAcum;
    int histAcum[256] = { 0 };
    int M = img.rows;
    int N = img.cols;
    histogramaAcumulado(img, &imgAcum, histAcum);

    for (int i = 0; i < img.rows; i++)
    {
        pfila_img = img.ptr<uchar>(i);
        pfila_imgEcu = imgEcu->ptr<uchar>(i);
        for (int j = 0; j < img.cols; j++)
        {
            pfila_imgEcu[j] = (histAcum[pfila_img[j]] * 255) / (M * N);
        }
    }
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
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            histAcum[i] = histAcum[i] + hist[j];
        }

    }
    int* maxIntensidad = max_element(&histAcum[0], &histAcum[255]);

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
