#pragma once

#include<Windows.h>
#include<conio.h>
#include"MatrixCalc.h"
//Funkce na vytisknuti matice bez kurzoru
void printRes(Matrix m);

//Funkce kter� �ek� na libovoln� input od u�ivatele
void waitTillPressed();

//Funkce kter� zobraz� n�vod
void tutorial();

//Funkce na v�pis menu
void printMainMenu(short selectedRow, const char* options[], int sizeOfOptions);

//Funkce kter� zobraz� �vodn� obrazovku
void startScreen();

//Funkce kter� spou�t� a provozuje hlavn� menu
int mainMenu(const char* options[], int sizeOfOptions);

//Funkce na napln�n� matice nulama
void fillMatrix(Matrix* m);

//Funkce na vytisknuti matice s kurzorem
void printMatrix(Matrix* m, int x, int y);

//Funcke kter� naskenuje ��slo od u�ivatele
double scanNum();

//Funkce kter� u�uje kam se bude zapisovat do matice
int matrixSelection(Matrix* m);

//Funkce kter� zapisuje do matice
int matrixInput(Matrix* m);

//Funkce kter� vypisuje a provozuje meny kalkula�ky
int calculationMenu(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions);

//Funkce kter� zaji��uje p�ed�n� matice k v�po�t�m
int calculationHandle(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions, Matrix* result);

//------------------------------------------------------------------ HISTORY ------------------------------------------------------

void saveMatrixToFile(Matrix matrix);

void printMatrixFromFile();

void loadMatrixFromFile(Matrix* mat);