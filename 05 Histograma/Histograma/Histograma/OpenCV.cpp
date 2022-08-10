// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histograma(Mat img, Mat* grafica, int* h);

int main()
{
    Mat img = imread("antenaOK.jpg",IMREAD_GRAYSCALE);
    imshow("imagen", img);
    Mat imgOpenCV = imread("antenaOK.jpg");

    vector<Mat> imgVec;
    split(imgOpenCV, imgVec);

    Mat grafica;
    uchar* pfila;
    int h[256] = { 0 };
    histograma(img, &grafica, h);
    imshow("histograma", grafica);

    Mat grafica2;
    float range[] = { 0,256 };
    const float* pRange = { range };
    int hSize = 256;
    bool uniform = true;
    bool accumulate = false;
    calcHist(&imgVec[0], 1,0, Mat(), grafica2,1, &hSize, &pRange, uniform,accumulate);

    
    Mat grafica3(256, 256, CV_8UC1);
    float vec[256] = {0};
    float* pImg; 
    uchar* pImg2;
    for (int i = 0; i < 256; i++) {
        pImg = grafica2.ptr<float>(i);
        vec[i] = pImg[0];
        cout <<"h["<<i<<"] = "<<vec[i]<<endl;
    }
    float* maxIntensidad = max_element(&vec[0], &vec[256]);
    cout << *maxIntensidad<<endl;
    int alto;
    for (int i = 0; i < 256; i++)
    {
        alto = (int)vec[i] * 256 / (*maxIntensidad);
        //cout << alto << endl;
        for (int j = 0; j < alto ; j++)
        {
            pImg2 = grafica3.ptr<uchar>(grafica3.rows - j - 1);
            pImg[i] = i;
        }
    }
    imshow("histograma openCV", grafica3);
    waitKey(0);
    
}
void histograma(Mat img, Mat* grafica, int* h)
{
    uchar* pImg;
    for (int i = 0; i < img.rows; i++)
    {
        pImg = img.ptr<uchar>(i);
        for (int j = 0; j < img.cols; j++)
        {
            h[pImg[j]]++;
        }
    }

    int* maxIntensidad = max_element(&h[0], &h[256]);
    grafica->create(256, 256, CV_8UC1);

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < h[i] * 256 / (*maxIntensidad); j++)
        {
            pImg = grafica->ptr<uchar>(grafica->rows - j - 1);
            pImg[i] = i;
        }
    }
}
