// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

#define PI 3.1416

using namespace std;
using namespace cv;

void escalar(Mat img_src, Mat *img_dst, float fx, float fy);
void rotar(Mat img_src, Mat* img_dst, double anguloRad);
void rotar90(Mat img_src, Mat* img_dst, int ang);
void trasladar(Mat img_src, Mat* img_dst, int tx, int ty);
void sesgadoVertical(Mat img_src, Mat* img_dst, float sv);
void sesgadoHorizontal(Mat img_src, Mat* img_dst, float sh);

int main()
{
    Mat imagen = imread("tiburon.jpg",IMREAD_GRAYSCALE);
    imshow("Imagen1", imagen);

    // Escalamiento
    Mat imagenGrande;
    float fx1 = 0.8;
    float fy1 = 0.2;
    escalar(imagen, &imagenGrande, fx1, fy1);
    imshow("Imagen al doble", imagenGrande);
    /*Mat imagenChica;
    float fx2 = 0.5;
    float fy2 = 0.7;
    escalar(imagen, &imagenChica, fx2, fy2);
    imshow("Imagen chica", imagenChica);

    //Escalamiento con openCV
    Mat imagenGrandeOpenCV;
    resize(imagen, imagenGrandeOpenCV,Size(imagen.cols*fy1, imagen.rows * fx1),fx1,fy1,INTER_LINEAR);
    imshow("Imagen al doble con openCV", imagenGrandeOpenCV);
    Mat imagenChicaOpenCV;
    resize(imagen, imagenChicaOpenCV, Size(imagen.cols * fy2, imagen.rows * fx2), fx2, fy2, INTER_LINEAR);
    imshow("Imagen chica openCV", imagenChicaOpenCV);

    //Rotacion
    Mat imgenRotada45;
    double grados= -10;
    double radianes = grados * PI / 180;
    rotar(imagen, &imgenRotada45,radianes);
    imshow("Imagen rotada 10", imgenRotada45);

    rotar(imagen, &imgenRotada45, -30 * PI / 180);
    imshow("Imagen rotada 30", imgenRotada45);

    rotar(imagen, &imgenRotada45, -45 * PI / 180);
    imshow("Imagen rotada 45", imgenRotada45);

    rotar(imagen, &imgenRotada45,-50 * PI / 180);
    imshow("Imagen rotada 50", imgenRotada45);

    rotar(imagen, &imgenRotada45, -90 * PI / 180);
    imshow("Imagen rotada 90", imgenRotada45);
   

    Mat imagenRotada90;
    rotar90(imagen, &imagenRotada90, 90);
    imshow("Imagen rotada 90", imagenRotada90);

    Mat imagenRotada_menos90;
    rotar90(imagen, &imagenRotada_menos90, -90);
    imshow("Imagen rotada -90", imagenRotada_menos90);

    Mat imagenRotada180;
    rotar90(imagen, &imagenRotada180, 180);
    imshow("Imagen rotada 180", imagenRotada180);


    //Rotacion con OpenCV
    Mat imagenRotadaOpenCV_90;
    rotate(imagen, imagenRotadaOpenCV_90, ROTATE_90_CLOCKWISE);
    imshow("Imagen rotada 90 openCV", imagenRotadaOpenCV_90);

    Mat imagenRotadaOpenCV_menos90;
    rotate(imagen, imagenRotadaOpenCV_menos90, ROTATE_90_COUNTERCLOCKWISE);
    imshow("Imagen rotada -90 openCV", imagenRotadaOpenCV_menos90);

    Mat imagenRotadaOpenCV_180;
    rotate(imagen, imagenRotadaOpenCV_180, ROTATE_180);
    imshow("Imagen rotada 180 openCV", imagenRotadaOpenCV_180);

    // Trasladar
    Mat imagenTrasladada;
    trasladar(imagen, &imagenTrasladada, 50, 100);
    imshow("Imagen trasladada", imagenTrasladada);

    // Sesgado vertical
    Mat imagenSesVer;
    sesgadoVertical(imagen, &imagenSesVer,0.5);
    imshow("Imagen sesgada vertical", imagenSesVer);

    Mat imagenSesHor;
    sesgadoHorizontal(imagen, &imagenSesHor, 0.5);
    imshow("Imagen sesgada horizontal", imagenSesHor);

   /* // Transformaciones afines en openCV

    Mat T(2, 3, CV_32F);
    //Escalamiento
    Mat imgEsc_openCV;
    float x = 0.5, y = 0.5;
    T.at<float>(0, 0) = x;
    T.at<float>(0, 1) = 0;
    T.at<float>(0, 2) = 0;
    T.at<float>(1, 0) = 0;
    T.at<float>(1, 1) = y;
    T.at<float>(1, 2) = 0;

    warpAffine(imagen, imgEsc_openCV, T, Size(imagen.cols*x, imagen.rows*y));
    imshow("Escalamiento openCV", imgEsc_openCV);

    //Rotacion
  

    //Traslacion
    Mat imgTraslacion;
    x = 10; y = 50;
    T.at<float>(0, 0) = 1;
    T.at<float>(0, 1) = 0;
    T.at<float>(0, 2) = x;
    T.at<float>(1, 0) = 0;
    T.at<float>(1, 1) = 1;
    T.at<float>(1, 2) = y;
   
    warpAffine(imagen, imgTraslacion, T, Size(imagen.cols, imagen.rows));
    imshow("Traslacion openCV", imgTraslacion);*/



    waitKey(0);   
}

void escalar(Mat img_src, Mat *img_dst, float fx, float fy)
{
    float T[3][3] = { {fx, 0, 0}, {0, fy, 0}, {0, 0, 1} };
    int* v, * w, min_v, min_w, k = 0;
    int* pMax_v, * pMax_w;
    int vecSize = img_src.rows * img_src.cols;
    v = (int*)malloc(vecSize * sizeof(int));
    w = (int*)malloc(vecSize * sizeof(int));
    uchar* pfila_src, * pfila_dst;

    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            v[k] = x * T[0][0] + y * T[1][0] + T[2][0];
            w[k] = x * T[0][1] + y * T[1][1] + T[2][1];
            k++;
        }
    }
    
    pMax_v = max_element(v, v + vecSize);
    pMax_w = max_element(w, w + vecSize);

    img_dst->create(*pMax_v + 1, *pMax_w + 1, CV_8UC1);
    k = 0;
    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            pfila_dst = img_dst->ptr<uchar>(v[k]);
            pfila_dst[w[k]] = pfila_src[y];
            k++;
        }
    }

    free(v);
    free(w);
}
void rotar(Mat img_src, Mat* img_dst, double anguloRad)
{
    double T[3][3] = { {cos(anguloRad), sin(anguloRad), 0}, {-sin(anguloRad), cos(anguloRad), 0}, {0, 0, 1} };
    int* v, * w, min_v, min_w, k = 0;
    int* pMin_v, * pMax_v, * pMin_w, * pMax_w;
    int vecSize = img_src.rows * img_src.cols;
    v = (int*)malloc(vecSize * sizeof(int));
    w = (int*)malloc(vecSize * sizeof(int));
    uchar* pfila_src, * pfila_dst;

    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            v[k] = x * T[0][0] + y * T[1][0] + T[2][0];
            w[k] = x * T[0][1] + y * T[1][1] + T[2][1];
            k++;
        }
    }
    pMin_v = min_element(v, v + vecSize);
    pMin_w = min_element(w, w + vecSize);
    min_v = *pMin_v;
    min_w = *pMin_w;
    for (int i = 0; i < vecSize; i++)
    {
        v[i] = v[i] - min_v;
        w[i] = w[i] - min_w;
    }
    pMax_v = max_element(v, v + vecSize);
    pMax_w = max_element(w, w + vecSize);

    /*cout << "min_v: " << *pMin_v << endl;
    cout << "max_v: " << *pMax_v << endl;
    cout << "min_w: " << *pMin_w << endl;
    cout << "max_w: " << *pMax_w << endl;*/
    
    img_dst->create(*pMax_v+1, *pMax_w+1, CV_8UC1);
    k = 0;
    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            pfila_dst = img_dst->ptr<uchar>(v[k]);
            pfila_dst[w[k]] = pfila_src[y];
            k++;
        }
    }

    free(v);
    free(w);
}
void rotar90(Mat img_src, Mat* img_dst, int ang)
{
    uchar* pfila_src, * pfila_dst;
    if (ang == 90)
    {
        img_dst->create(img_src.cols, img_src.rows, CV_8UC1);
        for (int x = 0; x < img_src.rows; x++)
        {
            pfila_src = img_src.ptr<uchar>(x);
            for (int y = 0; y < img_src.cols; y++)
            {
                pfila_dst = img_dst->ptr<uchar>(y);
                pfila_dst[img_dst->cols - x-1] = pfila_src[y];
            }
        }
    }
    if (ang == -90)
    {
        img_dst->create(img_src.cols, img_src.rows, CV_8UC1);
        for (int x = 0; x < img_src.rows; x++)
        {
            pfila_src = img_src.ptr<uchar>(x);
            for (int y = 0; y < img_src.cols; y++)
            {
                pfila_dst = img_dst->ptr<uchar>(img_dst->rows-y-1);
                pfila_dst[x] = pfila_src[y];
            }
        }
    }
    if (ang == 180)
    {
        img_dst->create(img_src.rows, img_src.cols, CV_8UC1);
        for (int x = 0; x < img_src.rows; x++)
        {
            pfila_src = img_src.ptr<uchar>(x);
            for (int y = 0; y < img_src.cols; y++)
            {
                pfila_dst = img_dst->ptr<uchar>(img_dst->rows - x - 1);
                pfila_dst[img_dst->cols-y-1] = pfila_src[y];
            }
        }
    }
}
void trasladar(Mat img_src, Mat* img_dst, int tx, int ty)
{
    float T[3][3] = { {1, 0, 0}, {0, 1, 0}, {tx, ty, 1} };
    int v, w;
    img_dst->create(img_src.rows + tx, img_src.cols + ty, CV_8UC1);
    uchar* pfila_src, * pfila_dst;
    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            v = x * T[0][0] + y * T[1][0] + 1 * T[2][0];
            w = x * T[0][1] + y * T[1][1] + 1 * T[2][1];
            pfila_dst = img_dst->ptr<uchar>(v);
            pfila_dst[w] = pfila_src[y];
        }
    }
}
void sesgadoVertical(Mat img_src, Mat* img_dst, float sv)
{
    float T[3][3] = { {1, 0, 0}, {sv, 1, 0}, {0, 0, 1} };
    int v, w, inc;
    if (img_src.rows > img_src.cols) {
        inc = img_src.rows * sv;
    }
    else {
        inc = img_src.cols * sv;
    }
    img_dst->create(img_src.rows+inc, img_src.cols, CV_8UC1);
    uchar* pfila_src, * pfila_dst;
    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            v = x * T[0][0] + y * T[1][0] + 1 * T[2][0];
            w = x * T[0][1] + y * T[1][1] + 1 * T[2][1];
            pfila_dst = img_dst->ptr<uchar>(v);
            pfila_dst[w] = pfila_src[y];
        }
    }

}
void sesgadoHorizontal(Mat img_src, Mat* img_dst, float sh)
{
    float T[3][3] = { {1, sh, 0}, {0, 1, 0}, {0, 0, 1} };
    int v, w, inc;
    if (img_src.rows > img_src.cols) {
        inc = img_src.rows * sh;
    }
    else {
        inc = img_src.cols * sh;
    }
    img_dst->create(img_src.rows, img_src.cols + inc, CV_8UC1);
    uchar* pfila_src, * pfila_dst;
    for (int x = 0; x < img_src.rows; x++)
    {
        pfila_src = img_src.ptr<uchar>(x);
        for (int y = 0; y < img_src.cols; y++)
        {
            v = x * T[0][0] + y * T[1][0] + 1 * T[2][0];
            w = x * T[0][1] + y * T[1][1] + 1 * T[2][1];
            pfila_dst = img_dst->ptr<uchar>(v);
            pfila_dst[w] = pfila_src[y];
        }
    }

}