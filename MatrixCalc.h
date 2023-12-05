#pragma once

#include<math.h>
#include<stdlib.h>
#include<stdio.h>


#define MAX_ROWS 5
#define MAX_COLS 5

typedef struct {
    int rows;
    int cols;
    double data[MAX_ROWS][MAX_COLS];
} Matrix;

Matrix createMatrix(int rows, int cols);

// Funkce pro ur�en� hodnosti matice
int calculateRank(Matrix A);

// Funkce pro v�po�et transpozice matice
void calculateTranspose(Matrix A, Matrix* transpose);

// Funkce pro scitani matic
Matrix addMatrices(Matrix A, Matrix B, int* err);

// Funkce pro odicitani matic
Matrix subtractMatrices(Matrix A, Matrix B, int* err);

// Funkce pro nasobeni matic
Matrix multiplyMatrices(Matrix A, Matrix B, int* err);

// Funkce pro v�po�et inverzn� matice
Matrix inverseMatrix(Matrix A, int* err);

// Funkce pro v�po�et n�soben� skal�rem
Matrix multiplyWithScalar(Matrix A, int Scalar);

// Funkce pro v�po�et determinantu

//Anal�za ve kterou ��dku nebo sloupci matice je nejv�ce 0
int analizeMat(Matrix mat);

//Zmen�en� matice 4x4 na 3x3 podle nejlep��ho ��dku/sloupce
Matrix createMat3x3Shrink(Matrix mat, int col, int row);

//Pomocn� funcke pro po��t�n� determinantu 4x4 - podle ��dk�
double calculateDet4x4Row(Matrix mat, int bestRow);

//Pomocn� funcke pro po��t�n� determinantu 4x4 - podle slpupc�
double calculateDet4x4Col(Matrix mat, int bestCol);

//Funkce pro po��t�n� determinantu 2x2
double calculateDet2x2(Matrix mat);

//Funkce pro po��t�n� determinantu 3x3
double calculateDet3x3(Matrix mat);

//Funkce pro po��t�n� determinantu 4x4
double calculateDet4x4(Matrix mat);

//Funcke pro po��t�n� obecn�ho determinantu
double calculateDeterminant(Matrix mat, int* err);