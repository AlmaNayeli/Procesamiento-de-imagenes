// OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void copiarImagenGris(Mat destino, Mat origen);

int main()
{
    Mat imagen_original = imread("ah.jpg",IMREAD_GRAYSCALE);
    Mat imagen_original2 = imread("lenacolor.png", IMREAD_GRAYSCALE);
    imshow("Imagen original", imagen_original);

    Mat imagen_menos_contraste(imagen_original.rows, imagen_original.cols, CV_8UC1);
    Mat imagen_mas_contraste(imagen_original.rows, imagen_original.cols, imagen_original.type());
    Mat imagen_menos_brillo(imagen_original.rows, imagen_original.cols, imagen_original.type());
    Mat imagen_mas_brillo(imagen_original.rows, imagen_original.cols, imagen_original.type());
    Mat imagen_complemento(imagen_original.rows, imagen_original.cols, imagen_original.type());
    Mat imagen_combinada(imagen_original.rows, imagen_original.cols, imagen_original.type());

    //Copiar imágenes
    copiarImagenGris(imagen_menos_contraste, imagen_original); //imagen.copyTo(imagen_menos_contraste);
    //Copiar imágenes con openCV
    imagen_original.copyTo(imagen_mas_contraste);
    imagen_original.copyTo(imagen_menos_brillo);
    imagen_original.copyTo(imagen_mas_brillo);
    
    uchar* pfila_original;
    uchar* pfila_original2;
    uchar* pfila_contrasteMas;
    uchar* pfila_contrasteMenos;
    uchar* pfila_masBrillo;
    uchar* pfila_menosBrillo;
    uchar* pfila_complemento;
    uchar* pfila_combinada;
    double pixel;

    //Más y menos contraste
    for (int i = 0; i < imagen_original.rows; i++)
    {
        pfila_contrasteMas = imagen_mas_contraste.ptr<uchar>(i);
        pfila_contrasteMenos = imagen_menos_contraste.ptr<uchar>(i);
        for (int j = 0; j < imagen_original.cols; j++)
        {
            pixel = (double)pfila_contrasteMas[j] * 1.5;
            if (pixel > 255)
                pixel = 255;
            pfila_contrasteMas[j] = (uchar)pixel; // 50% más contraste
            pfila_contrasteMenos[j] = pfila_contrasteMenos[j] * 0.5; // 50% menos contraste
        }
    }
    imshow("Imagen mas contraste", imagen_mas_contraste);
    imshow("Imagen menos contraste", imagen_menos_contraste);

    // Mas y menos contraste a color
    Mat imagen_color = imread("lenacolor.png");
    Mat imagen_color_masContraste;
    imagen_color.copyTo(imagen_color_masContraste);

    Vec3b* pfila_imagen_color_masContraste;

    for (int i = 0; i < imagen_color.rows; i++)
    {
        pfila_imagen_color_masContraste = imagen_color_masContraste.ptr<Vec3b>(i);
        for (int j = 0; j < imagen_color.cols; j++)
        {
            pixel = (double)pfila_imagen_color_masContraste[j][0] + 100;
            if (pixel > 255)
                pixel = 255;
            pfila_imagen_color_masContraste[j][0] = (uchar)pixel; 
            pixel = (double)pfila_imagen_color_masContraste[j][1] + 100;
            if (pixel > 255)
                pixel = 255;
            pfila_imagen_color_masContraste[j][1] = (uchar)pixel;
            pixel = (double)pfila_imagen_color_masContraste[j][2] + 100;
            if (pixel > 255)
                pixel = 255;
            pfila_imagen_color_masContraste[j][2] = (uchar)pixel;
        }
    }
    imshow("Imagen mas contraste a color", imagen_color_masContraste);


    // Más y menos brillo
    for (int i = 0; i < imagen_original.rows; i++)
    {
        pfila_masBrillo = imagen_mas_brillo.ptr<uchar>(i);
        pfila_menosBrillo = imagen_menos_brillo.ptr<uchar>(i);
        for (int j = 0; j < imagen_original.cols; j++)
        {
            pixel = (double)pfila_masBrillo[j] + 100;
            if (pixel > 255)
                pixel = 255;
            pfila_masBrillo[j] = (uchar)pixel;
            pixel = (double)pfila_menosBrillo[j] - 100;
            if (pixel < 0)
                pixel = 0;
            pfila_menosBrillo[j] = (uchar)pixel;
        }
    }
    imshow("Imagen con mas brillo", imagen_mas_brillo);
    imshow("Imagen con menos brillo", imagen_menos_brillo);

    // Más y menos contraste y brillo con funciones de openCV
    Mat imagen_masContraste_openCV;
    Mat imagen_menosContraste_openCV;
    Mat imagen_masBrillo_openCV;
    Mat imagen_menosBrillo_openCV;

    imagen_original.convertTo(imagen_masContraste_openCV, -1, 1.5, 0);
    imagen_original.convertTo(imagen_menosContraste_openCV, -1, 0.5, 0);
    imagen_original.convertTo(imagen_masBrillo_openCV, -1, 1, 100);
    imagen_original.convertTo(imagen_menosBrillo_openCV, -1, 1, -100);
    imshow("Imagen mas contraste openCV", imagen_masContraste_openCV);
    imshow("Imagen menos contraste openCV", imagen_menosContraste_openCV);
    imshow("Imagen mas brillo openCV", imagen_masBrillo_openCV);
    imshow("Imagen menos brillo openCV", imagen_menosBrillo_openCV);

    //Complemento
    for (int i = 0; i < imagen_original.rows; i++)
    {
        pfila_original = imagen_original.ptr<uchar>(i);
        pfila_complemento = imagen_complemento.ptr<uchar>(i);
        for (int j = 0; j < imagen_original.cols; j++)
        {
            pfila_complemento[j] = 255 - pfila_original[j];
        }
    }
    imshow("Imagen complemento", imagen_complemento);

    //Combinación
    float w = 0.5;
    for (int i = 0; i < 500; i++)
    {
        pfila_original = imagen_original.ptr<uchar>(i);
        pfila_original2 = imagen_original2.ptr<uchar>(i);
        pfila_combinada = imagen_combinada.ptr<uchar>(i);
        for (int j = 0; j < 500; j++)
        {
            pfila_combinada[j] = (1 - w) * pfila_original[j] - w * pfila_original2[j];
        }
    }
    imshow("Imagen combinada", imagen_combinada);
    
       
    waitKey(0);
}
void copiarImagenGris(Mat destino, Mat origen)
{   
    uchar* pfila_origen, * pfila_destino;
    for (int i = 0; i < origen.rows; i++)
    {
        pfila_origen = origen.ptr<uchar>(i);
        pfila_destino = destino.ptr<uchar>(i);
        for (int j = 0; j < origen.cols; j++)
        {
            pfila_destino[j] = pfila_origen[j];
        }
    }
}
