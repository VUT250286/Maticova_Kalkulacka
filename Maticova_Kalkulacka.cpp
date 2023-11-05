#include"Maticova_kalkulacka.h"

#define MAX_ROWS 10
#define MAX_COLS 10

// Struktura pro reprezentaci matice
typedef struct {
    int rows;
    int cols;
    double data[MAX_ROWS][MAX_COLS];
} Matrix;

// Funkce pro inicializaci matice
Matrix createMatrix(int rows, int cols) {
    if (rows <= 0 || rows > MAX_ROWS || cols <= 0 || cols > MAX_COLS) {
        printf("Nespravne rozmery matice.\n");
        exit(1);
    }
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    return mat;
}

// Funkce pro výpočet transpozice matice
void calculateTranspose(Matrix A, Matrix* transpose) {
    int rows = A.rows;
    int cols = A.cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose->data[j][i] = A.data[i][j];
        }
    }
}

// Funkce pro scitani matic
Matrix addMatrices(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("Nelze scitat matice ruznych rozmeru.\n");
        exit(1);
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
Matrix subtractMatrices(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("Nelze odicitat matice ruznych rozmeru.\n");
        exit(1);
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
Matrix multiplyMatrices(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        printf("Nelze nasobit matice s temi rozmeri.\n");
        exit(1);
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

// Funkce pro výpočet inverzní matice
Matrix inverseMatrix(Matrix A) {
    if (A.rows != A.cols) {
        printf("Inverzni matice nelze vypocitat, protoze matice neni ctvercova.\n");
        exit(1);
    }

    int n = A.rows;
    Matrix result = createMatrix(n, n);

    // Inicializace rozšířené matice (původní matice A + jednotková matice)
    double augmentedMatrix[MAX_ROWS][2 * MAX_COLS];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A.data[i][j];
            augmentedMatrix[i][j + n] = (i == j) ? 1.0 : 0.0; // Jednotková matice
        }
    }

    // Gaussova eliminace - převod matice na horní trojúhelníkovou formu
    for (int k = 0; k < n; k++) {
        // Normalizace aktuálního řádku
        double pivot = augmentedMatrix[k][k];
        for (int j = 0; j < 2 * n; j++) {
            augmentedMatrix[k][j] /= pivot;
        }
        // Eliminace všech násobků pivotu v ostatních řádcích
        for (int i = 0; i < n; i++) {
            if (i != k) {
                double factor = augmentedMatrix[i][k];
                for (int j = 0; j < 2 * n; j++) {
                    augmentedMatrix[i][j] -= factor * augmentedMatrix[k][j];
                }
            }
        }
    }

    // Extrahování inverzní matice z rozšířené matice
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.data[i][j] = augmentedMatrix[i][j + n];
        }
    }

    return result;
}

// Funkce pro vstup matice od uzivatele
void inputMatrix(Matrix* mat) {
    printf("Zadejte prvky matice:\n");
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            scanf("%lf", &mat->data[i][j]);
        }
    }
}

// Funkce pro vystup matice
void displayMatrix(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%f\t", mat.data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n;

    printf("Zadejte rozmery maticy (radek sloupec): ");
    scanf("%d %d", &m, &n);

    Matrix matrixA = createMatrix(m, n);
    Matrix matrixB = createMatrix(m, n);

    printf("Zadejte prvni matici:\n");
    inputMatrix(&matrixA);

    printf("Zadejte druhou matici:\n");
    inputMatrix(&matrixB);

    printf("Prvni matice:\n");
    displayMatrix(matrixA);

    printf("Druha matice:\n");
    displayMatrix(matrixB);

    // Scitani
    Matrix sum = addMatrices(matrixA, matrixB);
    printf("Soucet matic:\n");
    displayMatrix(sum);

    // Odcitani
    Matrix diff = subtractMatrices(matrixA, matrixB);
    printf("Rozdil matic:\n");
    displayMatrix(diff);

    // Nasobeni
    Matrix product = multiplyMatrices(matrixA, matrixB);
    printf("Nasobeni matic:\n");
    displayMatrix(product);

    // Výpočet inverzní matice
    if (m == n) {
        Matrix invA = inverseMatrix(matrixA);
        printf("Inverzni matice:\n");
        displayMatrix(invA);
    }
    else {
        printf("Inverzni matice nelze vypocitat, protoze matice neni ctvercova.\n");
    }

    // Výpočet transpozice
    Matrix transposeA = createMatrix(n, m);

    calculateTranspose(matrixA, &transposeA);

    printf("Transpozice matice:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f\t", transposeA.data[i][j]);
        }
        printf("\n");
    }


    return 0;
}
