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

// Funkce pro urèení hodnosti matice
int calculateRank(Matrix A);

// Funkce pro výpoèet transpozice matice
void calculateTranspose(Matrix A, Matrix* transpose);

// Funkce pro scitani matic
Matrix addMatrices(Matrix A, Matrix B, int* err);

// Funkce pro odicitani matic
Matrix subtractMatrices(Matrix A, Matrix B, int* err);

// Funkce pro nasobeni matic
Matrix multiplyMatrices(Matrix A, Matrix B, int* err);

// Funkce pro výpoèet inverzní matice
Matrix inverseMatrix(Matrix A, int* err);

// Funkce pro výpoèet násobení skalárem
Matrix multiplyWithScalar(Matrix A, int Scalar);

// Funkce pro výpoèet determinantu

//Analýza ve kterou øádku nebo sloupci matice je nejvíce 0
int analizeMat(Matrix mat);

//Zmenšení matice 4x4 na 3x3 podle nejlepšího øádku/sloupce
Matrix createMat3x3Shrink(Matrix mat, int col, int row);

//Pomocná funcke pro poèítání determinantu 4x4 - podle øádkù
double calculateDet4x4Row(Matrix mat, int bestRow);

//Pomocná funcke pro poèítání determinantu 4x4 - podle slpupcù
double calculateDet4x4Col(Matrix mat, int bestCol);

//Funkce pro poèítání determinantu 2x2
double calculateDet2x2(Matrix mat);

//Funkce pro poèítání determinantu 3x3
double calculateDet3x3(Matrix mat);

//Funkce pro poèítání determinantu 4x4
double calculateDet4x4(Matrix mat);

//Funcke pro poèítání obecného determinantu
double calculateDeterminant(Matrix mat, int* err);