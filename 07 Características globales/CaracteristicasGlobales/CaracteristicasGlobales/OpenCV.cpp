// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histograma(Mat img, Mat* imgHistograma, int* hist);
float calcBrillo(Mat img);
int calcContraste(Mat img);
int calcDinamica(Mat img);

int main()
{
    //Mat img = imread("caballo.jpg", IMREAD_GRAYSCALE);
    Mat img = imread("caballo2.jpg", IMREAD_GRAYSCALE);
    //Mat img = imread("antenaOK.jpg", IMREAD_GRAYSCALE);
    imshow("imagen", img);

    Mat imgHistograma;
    int hist[256] = { 0 };
    histograma(img, &imgHistograma, hist);
    imshow("Histograma", imgHistograma);

    for (int i = 0; i < 256; i++)
    {
        printf("Intensidad %d = %d\n", i, hist[i]);
    }

    float brillo = calcBrillo(img);
    printf("Brillo = %f\n", brillo);

    int contraste = calcContraste(img);
    printf("Contraste = %d\n", contraste);

    int dinamica = calcDinamica(img);
    printf("Dinamica = %d\n", dinamica);

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
float calcBrillo(Mat img)
{
    float brillo = 0;
    Mat imgHistograma;
    int hist[256] = { 0 };
    histograma(img, &imgHistograma, hist);
    for (int i = 0; i < 256; i++)
    {
        brillo = brillo + (i * hist[i]);
    }
    brillo = brillo / (img.rows * img.cols);
    return brillo;
}
void calcBrillo(Mat img, float* hb, float* phb) {
	*hb = 0;
	int N = img.rows;
	int M = img.cols;
	Mat grafica_h;
	int h[256] = { 0 };
	histograma(img, h, &grafica_h);
	imshow("Histograma", grafica_h);
	for (int i = 0; i < 256; i++) {
		*hb = *hb + i * h[i];
	}
	*hb = *hb / (N * M);
	*phb = *hb * 100 / 255;
}
int calcContraste(Mat img)
{
    int contraste,  maxIntensidad=256, minIntensidad=0;
    Mat imgHistograma;
    int hist[256] = { 0 };
    histograma(img, &imgHistograma, hist);
    for (int i = 0; i < 256; i++)
    {
        if (hist[i] != 0)
        {
            minIntensidad = i;
            break;
        }
    }
    for (int i = 255; i >= 0; i--)
    {
        if (hist[i] != 0)
        {
            maxIntensidad = i;
            break;
        }
    }
    contraste = maxIntensidad - minIntensidad;
    return contraste;

}
int calcDinamica(Mat img)
{
    int dinamica = 0;
    Mat imgHistograma;
    int hist[256] = { 0 };
    histograma(img, &imgHistograma, hist);
    for (int i = 0; i < 256; i++)
    {
        if (hist[i] != 0)
            dinamica++;
    }
    return dinamica;
}