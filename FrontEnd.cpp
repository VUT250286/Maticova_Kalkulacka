#include"FrontEnd.h"

void printRes(Matrix m) {
    for (size_t i = 0; i < m.rows; i++)
    {
        for (size_t j = 0; j < m.cols; j++)
        {
            printf("%0.2lf ", m.data[i][j]);
        }
        printf("\n");
    }
}

void waitTillPressed() {
    while (!_kbhit()) {
    }
    _getch();
}

void tutorial() {
    system("cls");
    puts("Vitej u navodu k maticove kalkulace.");
    puts("Pokud se ti povedlo dostat az sem, tak jsi urcite zjistil, ze se kalkulacka ovlada pomoci sipek a enteru.");
    puts("V prubehu pouzivani bude takovychle menu hned nekolik.");
    puts("Pro zacatek pouzivani nejprve musis zadat alespon jednu matici. Provedes to tim zpusobem, ze v menicku vyberes moznost pro danou matici.");
    puts("Program te vyzve k zadani velikosti matice, kterou zadas ve formatu \"m n\", pricemz m je pocet radku a n je pocet sloupcu.");
    puts("Po potvrzeni dimenzi enterem budes presunut k samotnemu zadavani hodnot. Pohyb po poli opet zajistuji sipky.");
    puts("Kdyz najedes na pole do ktereho chcec zapsat hodnotu, zmacknes enter a budes vyzvan k zadani hodnotym kterou nasledne potvrdis enterem.");
    puts("Az bude se svym vyberem hodnot spokojen, zmacnes mezernik pro ulozeni matice a budes presunut spet do hlavniho menu.\n\n");
    puts("Dalsi zpusob  zadani je nacist posledni vypoctenou matici z historie. Tuhle moznost opet najdes v hlavnim meny.");
    puts("Po te co budeš mit zadané matice, zvol možnost kalkulaèka.");
    puts("V tomhle meny budeš mit moznost na výber z mnoha operaci.");
    puts("Pokud bude vysledek matice, zobrazi se a ulozz se do historie.");
    puts("Pokud bude vysledek jen cislo (napr. u determinantu), pouze se zobrazi.\n\n");
    puts("Zmackni cokoliv pro navrat do meny...");

    waitTillPressed();
}

void printMainMenu(short selectedRow, const char* options[], int sizeOfOptions) {
    system("cls");
    //printf("%d, size %d\n", selectedRow, sizeOfOptions);
    int realNum = selectedRow % sizeOfOptions;
    if (realNum < 0)
        realNum += sizeOfOptions;

    for (size_t i = 0; i < sizeOfOptions; i++)
    {
        if (i == realNum)
            printf(">");

        printf("\t\t\t%s\n", options[i]);
    }
}

void startScreen() {
    printf("___  ___      _   _                       _   __      _ _          _            _         \n");
    printf("|  \\/  |     | | (_)                     | | / /     | | |        | |          | |        \n");
    printf("| .  . | __ _| |_ _  ___ _____   ____ _  | |/ /  __ _| | | ___   _| | __ _  ___| | ____ _ \n");
    printf("| |\\/| |/ _` | __| |/ __/ _ \\ \\ / / _` | |    \\ / _` | | |/ / | | | |/ _` |/ __| |/ / _` |\n");
    printf("| |  | | (_| | |_| | (_| (_) \\ V / (_| | | |\\  \\ (_| | |   <| |_| | | (_| | (__|   < (_| |\n");
    printf("\\_|  |_/\\__,_|\\__|_|\\___\\___/ \\_/ \\__,_| \\_| \\_/\\__,_|_|_|\\_\\\\__,_|_|\\__,_|\\___|_|\\_\\__,_|\n");
    printf("\n\n");
    printf("Naprogramovano Davidem Marholdem a Vitem Nemeckem\n\n");


    printf("Zmackni libovolnou klavesu pro pokracovani...\n");
    while (!_kbhit()) {
    }
    _getch();
}

int mainMenu(const char* options[], int sizeOfOptions) {
    HANDLE hStdin;
    INPUT_RECORD irInputRecord;
    DWORD dwEventsRead;
    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE) {
        return -1;
    }

    int counter = 0;
    int insideCounter = 0;
    printMainMenu(counter, options, sizeOfOptions);

    while (1) {
        ReadConsoleInput(hStdin, &irInputRecord, 1, &dwEventsRead);

        insideCounter = counter % sizeOfOptions;
        if (insideCounter < 0)
            insideCounter += (sizeOfOptions);

        if (irInputRecord.EventType == KEY_EVENT &&
            irInputRecord.Event.KeyEvent.bKeyDown) {

            switch (irInputRecord.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP: //printf("Up arrow key pressed.\n");
                counter--;
                printMainMenu(counter, options, sizeOfOptions);

                break;
            case VK_DOWN: //printf("Down arrow key pressed.\n");
                counter++;
                printMainMenu(counter, options, sizeOfOptions);

                break;
            case VK_RETURN:
                //printf("%d was selected", insideCounter);
                return insideCounter;
                break;
            default:
                break;
            }
        }
    }
}

void fillMatrix(Matrix* m) {
    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t h = 0; h < m->cols; h++)
        {
            m->data[i][h] = 0;
        }
    }
}

void printMatrix(Matrix* m, int x, int y) {
    x %= m->rows;
    if (x < 0)
        x += m->rows;

    y %= m->cols;
    if (y < 0)
        y += m->cols;

    system("cls");
    printf("Zmackni mezernik pro ulozeni matice nebo enter pro zadani cisla\n");
    printf("X: %d, Y: %d\n", x, y);
    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t h = 0; h < m->cols; h++)
        {
            if (i == x && h == y) {
                printf("___\t");
                continue;
            }

            printf("%0.2lf\t", m->data[i][h]);
        }
        printf("\n");
    }
}

double scanNum() {
    double x;
    char c[10];
    printf("Zadej cislo:");
    if (scanf(" %lf", &x) != 1)
    {
        printf("Spatne zadane cislo, vracim nulu, zmackni libovolnou klavesu pro pokracovani\n");
        scanf_s("%s", c, 10);
        fflush(stdin);
        waitTillPressed();
        return 0;
    }
    return x;
}

int matrixSelection(Matrix* m) {
    HANDLE hStdin;
    INPUT_RECORD irInputRecord;
    DWORD dwEventsRead;
    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE) {
        return -1;
    }
    int counterX = 0, counterY = 0;
    printMatrix(m, counterX, counterY);

    counterX %= m->rows;
    if (counterX < 0)
        counterX += m->rows;

    counterY %= m->cols;
    if (counterY < 0)
        counterY += m->cols;

    while (1) {
        fflush(stdin);
        ReadConsoleInput(hStdin, &irInputRecord, 1, &dwEventsRead);

        if (irInputRecord.EventType == KEY_EVENT &&
            irInputRecord.Event.KeyEvent.bKeyDown) {

            switch (irInputRecord.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:
                counterX--;
                printMatrix(m, counterX, counterY);
                break;
            case VK_DOWN:
                counterX++;
                printMatrix(m, counterX, counterY);

                break;
            case VK_RIGHT:
                counterY++;
                printMatrix(m, counterX, counterY);

                break;
            case VK_LEFT:
                counterY--;
                printMatrix(m, counterX, counterY);

                break;
            case VK_RETURN:
                double num;
                num = scanNum();
                m->data[counterX][counterY] = num;
                printMatrix(m, counterX, counterY);
                break;
            case VK_SPACE:
                return 0;
            default:
                break;
            }
        }
    }
}

int matrixInput(Matrix* m) {

    int needsFilling = (m->cols == 0 || m->rows == 0);

    if (m->cols != 0 && m->rows != 0)
    {
        printf("Chceste zadat novou matici? y/n:\n");
        fflush(stdin);
        char c;
        scanf(" %c", &c);
        if (c == 'n')
        {
            goto mS;
        }
        needsFilling = 1;

    }

    printf("Zadej velikost matice(maximalne 5x5) ve formatu m n: ");
    if ((scanf(" %d %d", &m->rows, &m->cols) != 2)) {
        printf("Spatne zadane dimenze.\n Zamackene libovolne tlacitko pro pokracovani.");
        waitTillPressed();
        return 1;
    }
    if (m->rows <= 0 || m->cols <= 0 || m->rows > 5 || m->cols > 5 || (m->cols == 1 || m->rows == 1))
    {
        printf("Neplatna dimenze\n");
        printf("Spatne zadane dimenze.\n Zamackene libovolne tlacitko pro pokracovani.");
        waitTillPressed();
        return 1;
    }

    if (needsFilling)
        fillMatrix(m);
mS:
    matrixSelection(m);

    while (!_kbhit()) {
    }
    _getch();

}

int calculationMenu(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions) {
    HANDLE hStdin;
    INPUT_RECORD irInputRecord;
    DWORD dwEventsRead;
    hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE) {
        return -1;
    }

    int counter = 0;
    printMainMenu(counter, options, sizeOfOptions);
    while (1) {
        ReadConsoleInput(hStdin, &irInputRecord, 1, &dwEventsRead);

        counter %= sizeOfOptions;
        if (counter < 0)
            counter += sizeOfOptions;

        if (irInputRecord.EventType == KEY_EVENT &&
            irInputRecord.Event.KeyEvent.bKeyDown) {

            switch (irInputRecord.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:
                counter--;
                printMainMenu(counter, options, sizeOfOptions);
                break;
            case VK_DOWN:
                counter++;
                printMainMenu(counter, options, sizeOfOptions);

                break;
            case VK_RETURN:
                return counter;
                break;
            default:
                break;
            }
        }
    }
}

int calculationHandle(Matrix* matA, Matrix* matB, const char* options[], int sizeOfOptions, Matrix* result) {

    if (matA->cols == 0 || matA->rows == 0 || matB->cols == 0 || matB->rows == 0)
    {
        printf("Jedna z matic je prazdna\nZmackni ckookliv pro navrat do meny...\n");
        waitTillPressed();
        return 1;
    }

    int res = calculationMenu(matA, matB, options, sizeOfOptions);
    int err = 0;
    if (res == sizeOfOptions - 1)
        return 0;

    switch (res)
    {
    case 0:
        *result = addMatrices(*matA, *matB, &err);
        if (err != 0)
        {
            err = 0;
            printf("Nelze scicat ruzne velke matice, vracim se dohlavniho meny\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        printf("Matice uspesne sectena a ulozena do historie\n");
        printRes(*result);
        waitTillPressed();
        return 0;
        break;
    case 1:
        *result = subtractMatrices(*matA, *matB, &err);
        if (err != 0)
        {
            err = 0;
            printf("Nelze odcitat ruzne velke matice, vracim se dohlavniho meny\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        printf("Matice uspesne odectena a ulozena do historie\n");
        printRes(*result);
        waitTillPressed();
        return 0;
        break;
    case 2:
        int scalar;
        printf("Zdaje cislo pro nasobeni: ");
        if (scanf("%d", &scalar) != 1)
        {
            printf("Spatne zadane cislo\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        *result = multiplyWithScalar(*matA, scalar);
        printf("Matice uspesne vynasobena skalarem a ulozena do historie\n");
        printRes(*result);
        waitTillPressed();
        return 0;
        break;

    case 3:
        *result = multiplyMatrices(*matA, *matB, &err);
        if (err != 0)
        {
            err = 0;
            printf("Nelze nasobit , vracim se dohlavniho meny\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        printf("Matice uspesne vynasobena a ulozena do historie\n");
        printRes(*result);
        waitTillPressed();
        return 0;
        break;
    case 4:
        calculateTranspose(*matA, result);
        printf("Matice uspesne transponovana a ulozena do historie\n");
        printRes(*result);
        waitTillPressed();
        return 0;
        break;

    case 5:
        *result = inverseMatrix(*matA, &err);
        if (err != 0)
        {
            err = 0;
            printf("Inverzni matice nelze vypocitat, protoze matice neni ctvercova\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        printf("Inverzni matice uspesne vypocitana a ulozena do historie\n");
        printRes(*result);
        waitTillPressed();
        return 0;
        break;

    case 6:
        double det;
        det = calculateDeterminant(*matA, &err);
        if (err == 1)
        {
            printf("Matice je vetsi nez 4x4\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        if (err == 2)
        {
            printf("Matice neni ctvercovat\nZmackni libovolnou klavesu pro pokracovani...");
            waitTillPressed();
            return 1;
        }
        printf("Determinant matice A je %0.2lf\n", det);
        waitTillPressed();
        return 0;
        break;
    case 7:
        int hod;
        hod = calculateRank(*matA);
        printf("Hodnost matice A je %d\n", hod);
        waitTillPressed();
        return 0;
        break;

    case -1:
        printf("Fatální chyba ukonèují program\n");
        exit(1);
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------ HISTORY ------------------------------------------------------

void saveMatrixToFile(Matrix matrix) {
    FILE* file = fopen("matice.txt", "w");

    if (file == NULL) {
        printf("Soubor nelze otevrit.\n");
        return;
    }

    // Uložit rozmìry matice do souboru
    fprintf(file, "Rows: %d\n", matrix.rows);
    fprintf(file, "Cols: %d\n", matrix.cols);

    // Oddìlovaè mezi "Cols" a hodnotami matice
    fprintf(file, "\n");

    // Uložit data matice do souboru
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            fprintf(file, "%lf ", matrix.data[i][j]);
        }
        fprintf(file, "\n");
    }

    // Zavøít soubor
    fclose(file);
}

void printMatrixFromFile() {
    // Otevøení souboru pro ètení
    FILE* file = fopen("matice.txt", "r");
    if (file == NULL) {
        perror("Chyba pri otevirani souboru");
    }

    // Naètení poètu øádkù a sloupcù
    Matrix mat = createMatrix(0, 0);
    fscanf(file, "Rows: %d\nCols: %d\n", &mat.rows, &mat.cols);

    // Naètení dat matice
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            fscanf(file, "%lf", &mat.data[i][j]);
        }
    }

    // Zavøení souboru
    fclose(file);

    // Výpis matice
    printf("Posledni matice vypoctena:\n");
    printRes(mat);
}

void loadMatrixFromFile(Matrix* mat) {
    // Otevøení souboru pro ètení
    FILE* file = fopen("matice.txt", "r");
    if (file == NULL) {
        perror("Chyba pri otevirani souboru");
        return;
    }

    // Naètení poètu øádkù a sloupcù
    fscanf(file, "Rows: %d\nCols: %d\n", &mat->rows, &mat->cols);

    // Naètení dat matice
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fscanf(file, "%lf", &mat->data[i][j]);
        }
    }

    // Zavøení souboru
    fclose(file);

    // Výpis, že naèítání bylo úspìšné
    printf("Data byla uspesne nactena ze souboru.\n");
}