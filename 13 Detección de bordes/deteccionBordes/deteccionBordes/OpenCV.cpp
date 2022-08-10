// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void bordes(Mat img_src, Mat* img_dst);
int main()
{
    Mat img = imread("figuras.png", IMREAD_GRAYSCALE);
    //Mat img = imread("lenacolor.png", IMREAD_GRAYSCALE);
    imshow("Imagen",img);

    Mat imgBordes(img.rows, img.cols, img.type());

    bordes(img, &imgBordes);
    imshow("Detección de bordes", imgBordes);


    waitKey(0);
    return 0;
}

void bordes(Mat img_src, Mat* img_dst)
{
    double grad_x, grad_y;
    int Hx[3][3] = { {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} };
    int Hy[3][3] = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };

    const int M = img_src.rows;
    const int N = img_src.cols;
    int vecSize = M * N;
    double minGrad_x = 100000;
    double minGrad_y = 100000;
    Mat imgGrad_x(img_src.rows, img_src.cols, img_src.type());
    Mat imgGrad_y(img_src.rows, img_src.cols, img_src.type());

    double * pGrad_x = new  double[vecSize];
    double* pGrad_y = new  double[vecSize];

    for (int i = 1; i < img_src.rows - 1; i++)
    {
        for (int j = 1; j < img_src.cols - 1; j++)
        {
            grad_x = (Hx[0][0] * img_src.at<uchar>(i - 1, j - 1) + Hx[0][1] * img_src.at<uchar>(i - 1, j) + Hx[0][2] * img_src.at<uchar>(i - 1, j + 1)
                  + Hx[1][0] * img_src.at<uchar>(i, j - 1) + Hx[1][1] * img_src.at<uchar>(i, j) + Hx[1][2] * img_src.at<uchar>(i, j + 1)
                  + Hx[2][0] * img_src.at<uchar>(i + 1, j - 1) + Hx[2][1] * img_src.at<uchar>(i + 1, j) + Hx[2][2] * img_src.at<uchar>(i + 1, j + 1))/2;

            pGrad_x[i * N + j] = grad_x;
            if (minGrad_x > grad_x)
                minGrad_x = grad_x;

            grad_y = (Hy[0][0] * img_src.at<uchar>(i - 1, j - 1) + Hy[0][1] * img_src.at<uchar>(i - 1, j) + Hy[0][2] * img_src.at<uchar>(i - 1, j + 1)
                + Hy[1][0] * img_src.at<uchar>(i, j - 1) + Hy[1][1] * img_src.at<uchar>(i, j) + Hy[1][2] * img_src.at<uchar>(i, j + 1)
                + Hy[2][0] * img_src.at<uchar>(i + 1, j - 1) + Hy[2][1] * img_src.at<uchar>(i + 1, j) + Hy[2][2] * img_src.at<uchar>(i + 1, j + 1))/2;

            pGrad_y[i * N + j] = grad_y;
            if (minGrad_y > grad_y)
                minGrad_y = grad_y;

            img_dst->at<uchar>(i, j) = sqrt((grad_x * grad_x) + (grad_y * grad_y));
            if (img_dst->at<uchar>(i, j) > 10)
                img_dst->at<uchar>(i, j) = 255;
            else
                img_dst->at<uchar>(i, j) = 0;
        }
    }
   
    cout << "minGrad_x: " << minGrad_x <<endl;
    cout << "minGrad_y: " << minGrad_y << endl;

    if (minGrad_x < 0)
    {
        for (int i = 0; i < vecSize; i++)
        {
            pGrad_x[i] = pGrad_x[i] - minGrad_x;
        }
    }
    if (minGrad_y < 0)
    {
        for (int i = 0; i < vecSize; i++)
        {
            pGrad_y[i] = pGrad_y[i] - minGrad_y;
        }
    }
    double* pMaxGrad_x = max_element(pGrad_x, pGrad_x + vecSize);
    double* pMaxGrad_y = max_element(pGrad_y, pGrad_y + vecSize);
    double maxGrad_x = *pMaxGrad_x;
    double maxGrad_y = *pMaxGrad_y;

    cout << "maxGrad_x: " << maxGrad_x << endl;
    cout << "maxGrad_y: " << maxGrad_y << endl;
  

    for (int i = 0; i < vecSize; i++)
    {
        pGrad_x[i] = (pGrad_x[i] / maxGrad_x) * 255;
        pGrad_y[i] = (pGrad_y[i] / maxGrad_y) * 255;
    }
   
    for (int i = 0; i < img_src.rows; i++)
    {
        for (int j = 0; j < img_src.cols; j++)
        {
            imgGrad_x.at<uchar>(i, j) = pGrad_x[i * N + j];
            imgGrad_y.at<uchar>(i, j) = pGrad_y[i * N + j];
        }
    }

    imshow("Gradiente x", imgGrad_x);
    imshow("Gradiente y", imgGrad_y);

}