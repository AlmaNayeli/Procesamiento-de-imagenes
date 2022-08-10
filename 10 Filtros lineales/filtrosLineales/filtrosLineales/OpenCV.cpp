// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void filtroBox(Mat img_src, Mat* img_dst);
void filtroGauss(Mat img_src, Mat* img_dst);
void filtroDiferencia(Mat img_src, Mat* img_dst);
int main()
{
    Mat img = imread("lenacolor.png", IMREAD_GRAYSCALE);
    imshow("imagen", img);

    Mat img2(img.rows, img.cols, img.type());
    filtroBox(img, &img2);
    imshow("Img filtro box", img2);

    //Mat imgBlur;
    //blur(img, imgBlur, Size(3, 3));
    //imshow("Blur 3", imgBlur);

    Mat imgBox3;
    int kernelSize = 3;
    Mat kernel3(kernelSize, kernelSize, CV_32F);
    kernel3 = Mat::ones(kernelSize, kernelSize, CV_32F) / (kernelSize* kernelSize);
    filter2D(img, imgBox3, CV_8U, kernel3);
    imshow("Filter2D box 3", imgBox3);

    Mat imgBox5;
    kernelSize = 9;
    Mat kernel5(kernelSize, kernelSize, CV_32F);
    kernel5 = Mat::ones(kernelSize, kernelSize, CV_32F) / (kernelSize * kernelSize);
    filter2D(img, imgBox5, img.depth(), kernel5);
    imshow("Filter2D box 5", imgBox5);

    //Mat imgBlur5;
    //blur(img, imgBlur5, Size(5, 5));
    //imshow("Blur 5", imgBlur5);

    filtroGauss(img, &img2);
    imshow("Img filtro Gauss", img2);

    Mat imgGauss3;
    //GaussianBlur(img, imgGauss3, Size(3, 3), 3, 3);
    kernelSize = 3;
    Mat kernelGauss3(kernelSize, kernelSize, CV_32F);

    kernelGauss3.at<float>(0, 0) = 0;
    kernelGauss3.at<float>(0, 1) = 0.166;
    kernelGauss3.at<float>(0, 2) = 0;
    kernelGauss3.at<float>(1, 0) = 0.166;
    kernelGauss3.at<float>(1, 1) = 0.333;
    kernelGauss3.at<float>(1, 2) = 0.166;
    kernelGauss3.at<float>(2, 0) = 0;
    kernelGauss3.at<float>(2, 1) = 0.166;
    kernelGauss3.at<float>(2, 2) = 0;
    //Para un filtro Gauss de 5x5, no poner la división directa como 1/57, sino con los decimales:0.017
   
    filter2D(img, imgGauss3, img.depth(), kernelGauss3);
    imshow("Filter2D Gauss3", imgGauss3);

    Mat imgGauss5;
    kernelSize = 5;
    Mat kernelGauss5(kernelSize, kernelSize, CV_32F);
    float gaussfiltro[5][5] = { {0,1,2,1,0},{1,3,5,3,1},{2,5,9,5,2},{1,3,5,3,1},{0,1,2,1,0} };
    for (int i = 0; i < kernelSize; i++)
    {
        for (int j = 0; j < kernelSize; j++)
        {
            kernelGauss5.at<float>(i,j) = gaussfiltro[i][j]/57;
        }
    }
    filter2D(img, imgGauss5, img.depth(), kernelGauss5);
    imshow("Filter2D Gauss5", imgGauss5);

    Mat img3(img.rows, img.cols, img.type());
    filtroDiferencia(img, &img3);
    imshow("Img filtro Diferencia", img3);

    Mat imgDif;
    kernelSize = 3;
    Mat kernelDif(kernelSize, kernelSize, CV_32F);
    float difFiltro[3][3] = { {0,-1,0},{-1,4,-1},{0,-1,0} };
    for (int i = 0; i < kernelSize; i++)
    {
        for (int j = 0; j < kernelSize; j++)
        {
            kernelDif.at<float>(i, j) = difFiltro[i][j];
        }
    }
    filter2D(img, imgDif, img.depth(), kernelDif);
    imshow("Filter2D diferencia", imgDif);

    Mat imgDif5;
    kernelSize = 5;
    Mat kernelDif5(kernelSize, kernelSize, CV_32F);
    float difFiltro5[5][5] = { {0,0,-1,0,0},{0,-1,-2,-1,0},{-1,-2,16,-2,-1},{0,-1,-2,-1,0},{0,0,-1,0,0} };
    for (int i = 0; i < kernelSize; i++)
    {
        for (int j = 0; j < kernelSize; j++)
        {
            kernelDif5.at<float>(i, j) = difFiltro5[i][j];
        }
    }
    filter2D(img, imgDif5, img.depth(), kernelDif5);
    imshow("Filter2D diferencia", imgDif5);

    
    filter2D(imgGauss5, imgGauss5, img.depth(), kernelDif5);
    imshow("Filter2D gauss y diferencia", imgGauss5);
    
    waitKey(0);
    
}
void filtroBox(Mat img_src, Mat* img_dst)
{
    double pixel;
    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            pixel =  (img_src.at<uchar>(i - 1, j - 1) + img_src.at<uchar>(i - 1, j) + img_src.at<uchar>(i - 1, j + 1)
                    + img_src.at<uchar>(i, j - 1) + img_src.at<uchar>(i, j) + img_src.at<uchar>(i, j + 1) 
                    + img_src.at<uchar>(i + 1, j - 1) + img_src.at<uchar>(i + 1, j) + img_src.at<uchar>(i + 1, j + 1))/9;

            img_dst->at<uchar>(i, j) = pixel;
        }
    }
}
void filtroGauss(Mat img_src, Mat* img_dst)
{
    double pixel;
    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            pixel = (0*img_src.at<uchar>(i - 1, j - 1) + 1*img_src.at<uchar>(i - 1, j) + 0*img_src.at<uchar>(i - 1, j + 1)
                    + 1*img_src.at<uchar>(i, j - 1) + 2*img_src.at<uchar>(i, j) + 1*img_src.at<uchar>(i, j + 1)
                    + 0*img_src.at<uchar>(i + 1, j - 1) + 1*img_src.at<uchar>(i + 1, j) + 0*img_src.at<uchar>(i + 1, j + 1)) / 6;

            img_dst->at<uchar>(i, j) = pixel;
        }
    }
}
void filtroDiferencia(Mat img_src, Mat* img_dst)
{
    double pixel;
    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            pixel = 0 * img_src.at<uchar>(i - 1, j - 1) + (-1 * img_src.at<uchar>(i - 1, j)) + 0 * img_src.at<uchar>(i - 1, j + 1)
                + (-1 * img_src.at<uchar>(i, j - 1)) + 4 * img_src.at<uchar>(i, j) + (-1 * img_src.at<uchar>(i, j + 1))
                + 0 * img_src.at<uchar>(i + 1, j - 1) + (-1 * img_src.at<uchar>(i + 1, j)) + 0 * img_src.at<uchar>(i + 1, j + 1);
            if (pixel < 0)
                pixel = 0;
            img_dst->at<uchar>(i, j) = pixel;
        }
    }
}