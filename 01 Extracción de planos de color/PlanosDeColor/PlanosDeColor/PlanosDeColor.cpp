// PlanosDeColor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat imagen = imread("lenacolor.png");// Mat imagen = imread("ah.jpg");
    imshow("Imagen original", imagen);

    Mat canal_azul_gris(imagen.rows, imagen.cols, CV_8UC1);
    Mat canal_rojo_gris(imagen.rows, imagen.cols, CV_8UC1);
    Mat canal_verde_gris(imagen.rows, imagen.cols, CV_8UC1);

    Mat canal_azul(imagen.rows, imagen.cols, CV_8UC3);
    Mat canal_rojo(imagen.rows, imagen.cols, CV_8UC3);
    Mat canal_verde(imagen.rows, imagen.cols, CV_8UC3);

 

    Vec3b* imagen_fila;
    Vec3b* canal_azul_fila;
    Vec3b* canal_rojo_fila;
    Vec3b* canal_verde_fila;

    uchar* azul_gris_fila;
    uchar* rojo_gris_fila;
    uchar* verde_gris_fila;

    for (int i = 0; i < imagen.rows; i++)
    {
        imagen_fila = imagen.ptr<Vec3b>(i);
        azul_gris_fila = canal_azul_gris.ptr<uchar>(i);
        rojo_gris_fila = canal_rojo_gris.ptr<uchar>(i);
        verde_gris_fila = canal_verde_gris.ptr<uchar>(i);
        for (int j = 0; j < imagen.cols; j++)
        {
            azul_gris_fila[j] = imagen_fila[j][0];
            verde_gris_fila[j] = imagen_fila[j][1];
            rojo_gris_fila[j] = imagen_fila[j][2];
        }
    }
    imshow("Canal azul en escala de grises", canal_azul_gris);
    imshow("Canal rojo en escala de grises", canal_rojo_gris);
    imshow("Canal verde en escala de grises", canal_verde_gris);

    for (int i = 0; i < imagen.rows; i++)
    {
        imagen_fila = imagen.ptr<Vec3b>(i); // Vec3b es un arreglo de 3 valores de tipo uchar (unsigned char)
        canal_azul_fila = canal_azul.ptr<Vec3b>(i);
        canal_rojo_fila = canal_rojo.ptr<Vec3b>(i);
        canal_verde_fila = canal_verde.ptr<Vec3b>(i);

        for (int j = 0; j < imagen.cols; j++)
        {
            canal_azul_fila[j][0] = imagen_fila[j][0];
            canal_azul_fila[j][1] = 0;
            canal_azul_fila[j][2] = 0;

            canal_verde_fila[j][0] = 0;
            canal_verde_fila[j][1] = 0;
            canal_verde_fila[j][2] = imagen_fila[j][2];

            canal_rojo_fila[j][0] = 0;
            canal_rojo_fila[j][1] = imagen_fila[j][1];
            canal_rojo_fila[j][2] = 0;

            
        }

    }
    imshow("Canal azul", canal_azul);
    imshow("Canal rojo", canal_rojo);
    imshow("Canal verde", canal_verde);

    imwrite("Canal_azul.jpg", canal_azul);

    waitKey(0);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
