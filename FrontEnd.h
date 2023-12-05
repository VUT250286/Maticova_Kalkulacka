#pragma once

#include<Windows.h>
#include<conio.h>
#include"MatrixCalc.h"
//Funkce na vytisknuti matice bez kurzoru
void printRes(Matrix m);

//Funkce která èeká na libovolnı input od uivatele
void waitTillPressed();

//Funkce která zobrazí návod
void tutorial();

//Funkce na vıpis menu
void printMainMenu(short selectedRow, const char* options[], int sizeOfOptions);

//Funkce která zobrazí úvodní obrazovku
void startScreen();

//Funkce která spouští a provozuje hlavní menu
int mainMenu(const char* options[], int sizeOfOptions);

//Funkce na naplnìní matice nulama
void fillMatrix(Matrix* m);

//Funkce na vytisknuti matice s kurzorem
void printMatrix(Matrix* m, int x, int y);

//Funcke která naskenuje èíslo od uivatele
double scanNum();

//Funkce která uèuje kam se bude zapisovat do matice
int matrixSelection(Matrix* m);

//Funkce která zapisuje do matice
int matrixInput(Matrix* m);

//Funkce která vypisuje a provozuje meny kalkulaèky
int calculationMenu(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions);

//Funkce která zajišuje pøedání matice k vıpoètùm
int calculationHandle(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions, Matrix* result);

//------------------------------------------------------------------ HISTORY ------------------------------------------------------

void saveMatrixToFile(Matrix matrix);

void printMatrixFromFile();

void loadMatrixFromFile(Matrix* mat);