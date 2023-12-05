#pragma once

#include<Windows.h>
#include<conio.h>
#include"MatrixCalc.h"

void printRes(Matrix m);

void waitTillPressed();

void tutorial();

void printMainMenu(short selectedRow, const char* options[], int sizeOfOptions);

void startScreen();

int mainMenu(const char* options[], int sizeOfOptions);

void fillMatrix(Matrix* m);

void printMatrix(Matrix* m, int x, int y);

double scanNum();

int matrixSelection(Matrix* m);

int matrixInput(Matrix* m);

int calculationMenu(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions);

int calculationHandle(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions, Matrix* result);

//------------------------------------------------------------------ HISTORY ------------------------------------------------------

void saveMatrixToFile(Matrix matrix);

void printMatrixFromFile();

void loadMatrixFromFile(Matrix* mat);