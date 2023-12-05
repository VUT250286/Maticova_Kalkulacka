#include"Maticova_kalkulacka.h"
#include"MatrixCalc.h"
#include"FrontEnd.h"

int main() {

    startScreen();
    const char* mainMenuOptions[] = { "Kalkulacka","Matice A","Matice B","Zobrazit historii","Nacist matici z historie [Matice A]","Nacist matici z historie [Matice B]","Navod","Konec"};
    const char* calculatorMenuOptions[] = { "Scitani matic","Odecitani matic","Nasobeni matice skalarem","Nasobeni matic","Transpozice Matice","Vypocet inverzni matice","Determinant matice","Urceni hodnosti matice","Zpet"};

    int sizeOfOptions = sizeof(mainMenuOptions) / sizeof(mainMenuOptions[0]);
    int sizeOfCalculatorOptions = sizeof(calculatorMenuOptions) / sizeof(calculatorMenuOptions[0]);

    Matrix mat1 = createMatrix(0, 0);
    Matrix mat2 = createMatrix(0, 0);

    Matrix res = createMatrix(0, 0);



    int historyErr = 0;
    while (true)
    {
        int selected = mainMenu(mainMenuOptions, sizeOfOptions);
        

        if (selected == sizeOfOptions - 1) {
            system("cls");
            printf("Program ukoncen\n");
            return 0;
        }

        switch (selected)
        {
        case -1: 
            printf("Program ukoncen.\n");
            return 0;
            break;
        case 0: //Calculator start
            historyErr = calculationHandle(&mat1,&mat2, calculatorMenuOptions, sizeOfCalculatorOptions, &res);
            break;
        case 1: // Matrix A input
            matrixInput(&mat1);
            break;
        case 2: // Matrix B input
            matrixInput(&mat2);
            break;
        case 3: // Zobrazit historii
            printMatrixFromFile();
            waitTillPressed();
            break;
        case 4: // Nacist matici z historie
            loadMatrixFromFile(&mat1);
            waitTillPressed();
            break;
        case 5: // Nacist matici z historie
            loadMatrixFromFile(&mat2);
            waitTillPressed();
            break;
        case 6: // tutorial
            tutorial();
            break;
        default: 
            return 1;
            break;
        }

        if (historyErr != 1 && selected==0) {
            saveMatrixToFile(res);
        }
    }
    return 0;
}