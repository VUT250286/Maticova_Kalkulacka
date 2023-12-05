#include "MatrixCalc.h"

// Funkce pro inicializaci matice
Matrix createMatrix(int rows, int cols) {

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    return mat;
}

// Funkce pro urèení hodnosti matice
int calculateRank(Matrix A) {
    int rank = 0;
    int lead = 0;  // Stupnì redukce (echelon form)

    while (lead < A.rows && lead < A.cols) {
        // Nalezne první nenulový prvek ve sloupci pod vedením
        int i = lead;
        while (i < A.rows && A.data[i][lead] == 0.0) {
            i++;
        }

        if (i == A.rows) {
            // Pokud jsou všechny prvky ve sloupci pod vedením nula, pøejdeme na další sloupec
            lead++;
        }
        else {
            // Jinak zvýšíme hodnost matice a provedeme eliminaci
            rank++;
            for (int j = 0; j < A.cols; j++) {
                double temp = A.data[i][j];
                A.data[i][j] = A.data[lead][j];
                A.data[lead][j] = temp;
            }

            // Normalizujeme øádek pod vedením
            double div = A.data[lead][lead];
            for (int j = 0; j < A.cols; j++) {
                A.data[lead][j] /= div;
            }

            // Eliminujeme prvky nad a pod vedením
            for (int i = 0; i < A.rows; i++) {
                if (i != lead) {
                    double factor = A.data[i][lead];
                    for (int j = 0; j < A.cols; j++) {
                        A.data[i][j] -= factor * A.data[lead][j];
                    }
                }
            }

            // Pøesuneme na další øádek
            lead++;
        }
    }

    return rank;
}

// Funkce pro výpoèet transpozice matice
void calculateTranspose(Matrix A, Matrix* transpose) {
    int rows = A.rows;
    int cols = A.cols;

    transpose->rows = cols;
    transpose->cols = rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose->data[j][i] = A.data[i][j];
        }
    }
}

// Funkce pro scitani matic
Matrix addMatrices(Matrix A, Matrix B, int* err) {
    Matrix dummy = createMatrix(0, 0);
    *err = 0;

    if (A.rows != B.rows || A.cols != B.cols) {
        //printf("Nelze scitat matice ruznych rozmeru.\n");
        *err = 1;
        return dummy;
    }

    Matrix result = createMatrix(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            result.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }
    return result;
}

// Funkce pro odicitani matic
Matrix subtractMatrices(Matrix A, Matrix B, int* err) {
    Matrix dummy = createMatrix(0, 0);
    *err = 0;

    if (A.rows != B.rows || A.cols != B.cols) {
        //printf("Nelze odicitat matice ruznych rozmeru.\n");
        *err = 1;
        return dummy;
    }

    Matrix result = createMatrix(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            result.data[i][j] = A.data[i][j] - B.data[i][j];
        }
    }
    return result;
}

// Funkce pro nasobeni matic
Matrix multiplyMatrices(Matrix A, Matrix B, int* err) {
    Matrix dummy = createMatrix(0, 0);
    *err = 0;
    if (A.cols != B.rows) {
        //printf("Nelze nasobit matice s temi rozmeri.\n");
        *err = 1;
        return dummy;
    }

    Matrix result = createMatrix(A.rows, B.cols);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < A.cols; k++) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    return result;
}

// Funkce pro výpoèet inverzní matice
Matrix inverseMatrix(Matrix A, int* err) {
    Matrix dummy = createMatrix(0, 0);
    *err = 0;
    if (A.rows != A.cols) {
        //printf("Inverzni matice nelze vypocitat, protoze matice neni ctvercova.\n");
        *err = 1;
        return dummy;

    }

    int n = A.rows;
    Matrix result = createMatrix(n, n);

    // Inicializace rozšíøené matice (pùvodní matice A + jednotková matice)
    double augmentedMatrix[MAX_ROWS][2 * MAX_COLS];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A.data[i][j];
            augmentedMatrix[i][j + n] = (i == j) ? 1.0 : 0.0; // Jednotková matice
        }
    }

    // Gaussova eliminace - pøevod matice na horní trojúhelníkovou formu
    for (int k = 0; k < n; k++) {
        // Normalizace aktuálního øádku
        double pivot = augmentedMatrix[k][k];
        for (int j = 0; j < 2 * n; j++) {
            augmentedMatrix[k][j] /= pivot;
        }
        // Eliminace všech násobkù pivotu v ostatních øádcích
        for (int i = 0; i < n; i++) {
            if (i != k) {
                double factor = augmentedMatrix[i][k];
                for (int j = 0; j < 2 * n; j++) {
                    augmentedMatrix[i][j] -= factor * augmentedMatrix[k][j];
                }
            }
        }
    }

    // Extrahování inverzní matice z rozšíøené matice
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.data[i][j] = augmentedMatrix[i][j + n];
        }
    }

    return result;
}

//------------------------------------------------------------------
double calculateDet2x2(Matrix mat) {
    //Sarusovo pravidlo
    return mat.data[0][0] * mat.data[1][1] - mat.data[1][0] * mat.data[0][1];
}

double calculateDet3x3(Matrix mat) {
    // a-0,0 b-0,1 c-0,2
    // d-1,0 e-1,1 f-1,2
    // g-2,0 h-2,1 i-2,2
    return (mat.data[0][0] * mat.data[1][1] * mat.data[2][2]) +
        (mat.data[1][0] * mat.data[2][1] * mat.data[0][2]) +
        (mat.data[2][0] * mat.data[0][1] * mat.data[1][2]) -
        (mat.data[2][0] * mat.data[1][1] * mat.data[0][2]) -
        (mat.data[0][0] * mat.data[2][1] * mat.data[1][2]) -
        (mat.data[1][0] * mat.data[0][1] * mat.data[2][2]);
}


int analizeMat(Matrix mat) {

    int zeroCount = 0;
    int bestRow = 0;
    int bestRowIndex = 0;

    int bestCol = 0;
    int bestColIndex = 0;
    //Analyze rows
    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            if (mat.data[i][j] == 0) //TODO: better comparasion
                zeroCount++;
        }

        if (zeroCount > bestRow) {
            bestRow = zeroCount;
            bestRowIndex = i;
        }

        zeroCount = 0;
    }
    //Analyze cols
    for (size_t i = 0; i < mat.cols; i++)
    {
        for (size_t j = 0; j < mat.rows; j++)
        {
            if (mat.data[j][i] == 0) //TODO: better comparasion
                zeroCount++;
        }

        if (zeroCount > bestCol) {
            bestCol = zeroCount;
            bestColIndex = i;
        }


        zeroCount = 0;
    }
    return bestCol > bestRow ? bestColIndex : bestRowIndex + 10;
}

Matrix createMat3x3Shrink(Matrix mat, int col, int row) {
    Matrix newMat;
    newMat.cols = 3;
    newMat.rows = 3;

    size_t counterI = 0;
    size_t counterJ = 0;

    for (size_t i = 0; i < mat.rows; i++)
    {
        if (i == row)
            continue;

        for (size_t j = 0; j < mat.rows; j++)
        {
            if (j == col)
                continue;
            newMat.data[counterI][counterJ] = mat.data[i][j];

            counterJ++;
        }
        counterJ = 0;
        counterI++;
    }
    return newMat;
}

double calculateDet4x4Row(Matrix mat, int bestRow) {
    double det = 0;
    //printf("Kalkulace podle radku %d\n", bestRow);
    for (size_t i = 0; i < mat.cols; i++)
    {
        if (mat.data[bestRow][i] == 0)
            continue;

        Matrix matx; matx.rows = 3; matx.cols = 3;
        matx = createMat3x3Shrink(mat, i, bestRow);
        /* displayMatrix(matx);
         printf("\n\n");*/
        det += pow(-1, bestRow + i) * mat.data[bestRow][i] * calculateDet3x3(matx);
    }

    return det;
}

double calculateDet4x4Col(Matrix mat, int bestCol) {
    double det = 0;
    //printf("Kalkulace podle sloupce %d\n", bestCol);
    for (size_t i = 0; i < mat.cols; i++)
    {
        if (mat.data[i][bestCol] == 0)
            continue;

        Matrix matx; matx.rows = 3; matx.cols = 3;
        matx = createMat3x3Shrink(mat, bestCol, i);
        /*displayMatrix(matx);
        printf("\n\n");*/
        det += pow(-1, bestCol + i) * mat.data[i][bestCol] * calculateDet3x3(matx);
    }

    return det;
}


double calculateDet4x4(Matrix mat) {

    if (analizeMat(mat) > 9)
        return calculateDet4x4Row(mat, analizeMat(mat) - 10);
    else
        return calculateDet4x4Col(mat, analizeMat(mat));
}

Matrix multiplyWithScalar(Matrix A, int Scalar) {
    for (size_t i = 0; i < A.cols; i++)
    {
        for (size_t j = 0; j < A.rows; j++) {
            A.data[i][j] *= Scalar;
        }
    }
    return A;
}

double calculateDeterminant(Matrix mat, int* err) {
    *err = 0;
    if (mat.cols > 4 || mat.rows > 4)
    {
        //printf("Matice je vetsi nez 4x4.\n");
        *err = 1;
        return 0;
    }

    if (mat.cols != mat.rows) {
        //printf("Matice neni ctvercova\n");
        *err = 2;
        return 0;
    }

    switch (mat.rows)
    {
    case 2:
        return calculateDet2x2(mat);
        break;

    case 3:
        return calculateDet3x3(mat);
        break;

    case 4:
        return calculateDet4x4(mat);
        break;

    default:
        printf("Begone\n");
        exit(1);
        break;
    }
}