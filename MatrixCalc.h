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


int analizeMat(Matrix mat);

Matrix createMat3x3Shrink(Matrix mat, int col, int row);

double calculateDet4x4Row(Matrix mat, int bestRow);

double calculateDet4x4Col(Matrix mat, int bestCol);

double calculateDet2x2(Matrix mat);

double calculateDet3x3(Matrix mat);

double calculateDet4x4(Matrix mat);

double calculateDeterminant(Matrix mat, int* err);