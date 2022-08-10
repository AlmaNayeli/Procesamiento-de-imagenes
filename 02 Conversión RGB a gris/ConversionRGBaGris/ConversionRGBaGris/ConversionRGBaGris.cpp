// ConversionRGBaGris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat imagenRGB = imread("ah.jpg");
    //Mat imagenRGB = imread("lenacolor.png");
    imshow("Imagen a color", imagenRGB);

    Mat imagenGris_prom(imagenRGB.rows, imagenRGB.cols, CV_8UC1);
    Mat imagenGris_luma1(imagenRGB.rows, imagenRGB.cols, CV_8UC1);
    Mat imagenGris_luma2(imagenRGB.rows, imagenRGB.cols, CV_8UC1);
    Mat imagenGris_luma3(imagenRGB.rows, imagenRGB.cols, CV_8UC1);
    Mat imagenGris_desaturacion(imagenRGB.rows, imagenRGB.cols, CV_8UC1);
    Mat imagenGris_descomposicionMin(imagenRGB.rows, imagenRGB.cols, CV_8UC1);
    Mat imagenGris_descomposicionMax(imagenRGB.rows, imagenRGB.cols, CV_8UC1);

    Vec3b* pfila_imagenRGB;
    uchar* pfila_imagenGris_prom;
    uchar* pfila_imagenGris_luma1;
    uchar* pfila_imagenGris_luma2;
    uchar* pfila_imagenGris_luma3;
    uchar* pfila_imagenGris_desaturacion;
    uchar* pfila_imagenGris_descomposicionMin;
    uchar* pfila_imagenGris_descomposicionMax;

    double pixel;
    uchar vector[3];
    uchar* pMax, * pMin;

    double r, g, b;
    // Metodo del promedio
    for (int i = 0; i < imagenRGB.rows; i++)
    {
        pfila_imagenRGB = imagenRGB.ptr<Vec3b>(i);
        pfila_imagenGris_prom = imagenGris_prom.ptr<uchar>(i);
        for (int j = 0; j < imagenRGB.cols; j++)
        {
            b = (double)pfila_imagenRGB[j][0];
            g = (double)pfila_imagenRGB[j][1];
            r = (double)pfila_imagenRGB[j][2];

           pixel = (r+g+b) / 3;
           pfila_imagenGris_prom[j] = (uchar)pixel;
        }
    }
    imshow("Método del promedio", imagenGris_prom);

    
    // Método Luma/Luminance
    for (int i = 0; i < imagenRGB.rows; i++)
    {
        pfila_imagenRGB = imagenRGB.ptr<Vec3b>(i);
        pfila_imagenGris_luma1 = imagenGris_luma1.ptr<uchar>(i);
        pfila_imagenGris_luma2 = imagenGris_luma2.ptr<uchar>(i);
        pfila_imagenGris_luma3 = imagenGris_luma3.ptr<uchar>(i);
        for (int j = 0; j < imagenRGB.cols; j++)
        {
            pfila_imagenGris_luma1[j] = pfila_imagenRGB[j][0] * 0.11 + pfila_imagenRGB[j][1] * 0.59 + pfila_imagenRGB[j][2] * 0.3;
            pfila_imagenGris_luma2[j] = pfila_imagenRGB[j][0] * 0.0722 + pfila_imagenRGB[j][1] * 0.7152 + pfila_imagenRGB[j][2] * 0.2126;
            pfila_imagenGris_luma3[j] = pfila_imagenRGB[j][0] * 0.114 + pfila_imagenRGB[j][1] * 0.587 + pfila_imagenRGB[j][2] * 0.299;
        }
    }
    imshow("Método Luma1", imagenGris_luma1);
    imshow("Método Luma2", imagenGris_luma2);
    imshow("Método Luma3", imagenGris_luma3);
    
    //Desaturación
    for (int i = 0; i < imagenRGB.rows; i++)
    {
        pfila_imagenRGB = imagenRGB.ptr<Vec3b>(i);
        pfila_imagenGris_desaturacion = imagenGris_desaturacion.ptr<uchar>(i);
        for (int j = 0; j < imagenRGB.cols; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                vector[k] = pfila_imagenRGB[j][k];
            }
            pMax = max_element(vector, vector + 3);
            pMin = min_element(vector, vector + 3);
            pfila_imagenGris_desaturacion[j] = (*pMax + *pMin)/2;
        }
    }
    imshow("Método desaturacion", imagenGris_desaturacion);

    // Descomposición mínima y máxima
    for (int i = 0; i < imagenRGB.rows; i++)
    {
        pfila_imagenRGB = imagenRGB.ptr<Vec3b>(i);
        pfila_imagenGris_descomposicionMin = imagenGris_descomposicionMin.ptr<uchar>(i);
        pfila_imagenGris_descomposicionMax = imagenGris_descomposicionMax.ptr<uchar>(i);
        for (int j = 0; j < imagenRGB.cols; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                vector[k] = pfila_imagenRGB[j][k];
            }
            pMax = max_element(vector, vector + 3);
            pMin = min_element(vector, vector + 3);
            pfila_imagenGris_descomposicionMin[j] = *pMin;
            pfila_imagenGris_descomposicionMax[j] = *pMax;
        }
    }
    imshow("Método descomposicion Minima", imagenGris_descomposicionMin);
    imshow("Método descomposicion Maxima", imagenGris_descomposicionMax);

    waitKey(0);
}

