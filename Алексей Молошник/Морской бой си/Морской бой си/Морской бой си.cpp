#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <clocale>
#include <cstring>
#include <windows.h>

const int DLINA = 12;
const int SHIRINA = 12;

void printGrid(char grid[DLINA][SHIRINA])
{
    printf("  | # А Б В Г Д Е Ж З И К \n");

    for (int i = 0; i < DLINA; i++)
    {
        if (i >= 1 && i <= 10)
        {
            printf("%2d  ", i);
        }
        else
        {
            printf("    ");
        }

        for (int j = 0; j < SHIRINA; j++)
        {
            printf("%c ", grid[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void initGrid(char grid[DLINA][SHIRINA])
{
    for (int i = 0; i < DLINA; i++)
    {
        for (int j = 0; j < SHIRINA; j++)
        {
            if (i == 0 || i == 11 || j == 0 || j == 11)
            {
                grid[i][j] = '#';
            }
            else
            {
                grid[i][j] = '.';
            }
        }
    }
}

void ship()
{
    printf("ВИДЫ КОРАБЛЕЙ И ИХ КОЛИЧЕСТВО:\n");
    printf("П - 4\n");
    printf("ПП - 3\n");
    printf("ППП - 2\n");
    printf("ПППП - 1\n\n");
}

int getColumn(char stolbStr[])
{
    if (strcmp(stolbStr, "А") == 0)
    {
        return 1;
    }
    else if (strcmp(stolbStr, "Б") == 0)
    {
        return 2;
    }
    else if (strcmp(stolbStr, "В") == 0)
    {
        return 3;
    }
    else if (strcmp(stolbStr, "Г") == 0)
    {
        return 4;
    }
    else if (strcmp(stolbStr, "Д") == 0)
    {
        return 5;
    }
    else if (strcmp(stolbStr, "Е") == 0)
    {
        return 6;
    }
    else if (strcmp(stolbStr, "Ж") == 0)
    {
        return 7;
    }
    else if (strcmp(stolbStr, "З") == 0)
    {
        return 8;
    }
    else if (strcmp(stolbStr, "И") == 0)
    {
        return 9;
    }
    else if (strcmp(stolbStr, "К") == 0)
    {
        return 10;
    }
    else
    {
        return 0;
    }
}

void enterDeck(char shipsGrid[DLINA][SHIRINA])
{
    int stroka;
    int stolb;
    char stolbStr[10];

    while (true)
    {
        printf("Введите число и букву столбца: ");
        scanf("%d %9s", &stroka, stolbStr);

        stolb = getColumn(stolbStr);

        if (stroka >= 1 && stroka <= 10 && stolb >= 1 && stolb <= 10 && shipsGrid[stroka][stolb] == '.')
        {
            shipsGrid[stroka][stolb] = 'П';
            printf("\nПоле после ввода палубы:\n");
            printGrid(shipsGrid);

            return;
        }
        else
        {
            printf("Ошибка! Корабли не должны быть вместе. Повторите ввод.\n");
        }
    }
}

void enterShips(char shipsGrid[DLINA][SHIRINA], int count, int decks, const char name[])
{
    printf("Введите координаты для %s:\n", name);

    for (int i = 1; i <= count; i++)
    {
        printf("Корабль %d:\n", i);

        for (int p = 1; p <= decks; p++)
        {
            printf("Палуба %d. ", p);
            enterDeck(shipsGrid);
        }
    }

    printf("\n");
}

void locationship(char shipsGrid[DLINA][SHIRINA])
{
    enterShips(shipsGrid, 4, 1, "однопалубных кораблей (П)");
    enterShips(shipsGrid, 3, 2, "двухпалубных кораблей (ПП)");
    enterShips(shipsGrid, 2, 3, "трёхпалубных кораблей (ППП)");
    enterShips(shipsGrid, 1, 4, "четырёхпалубного корабля (ПППП)");
}

bool input(char hitsGrid[DLINA][SHIRINA], char shipsGrid[DLINA][SHIRINA])
{
    int stroka;
    int stolb;
    char stolbStr[10];
    char nomber;

    printf("Введите число и букву или 0 для выхода: ");

    scanf("%d", &stroka);

    if (stroka == 0)
    {
        return false;
    }

    scanf("%9s", stolbStr);

    stolb = getColumn(stolbStr);

    if (stroka >= 1 && stroka <= 10 &&
        stolb >= 1 && stolb <= 10)
    {
        if (hitsGrid[stroka][stolb] == 'X' ||
            hitsGrid[stroka][stolb] == 'O')
        {
            printf("Вы уже стреляли в эту клетку!\n");
            return true;
        }

        if (shipsGrid[stroka][stolb] == 'П')
        {
            nomber = 'X';
            printf("Попадание!\n");
        }
        else
        {
            nomber = 'O';
            printf("Промах!\n");
        }

        hitsGrid[stroka][stolb] = nomber;

        return true;
    }
    else
    {
        printf("Неверные координаты!\n");
        return true;
    }
}

void enemyInput(char enemyGrid[DLINA][SHIRINA])
{
    int stroka;
    int stolb;
    char stolbStr[10];
    char answer;

    printf("\nПОЛЕ ПРОТИВНИКА\n");
    printf("Введите координаты выстрела или 0 для выхода: ");

    scanf("%d", &stroka);

    if (stroka == 0)
        return;

    scanf("%9s", stolbStr);

    stolb = getColumn(stolbStr);

    if (stroka < 1 || stroka > 10 ||
        stolb < 1 || stolb > 10)
    {
        printf("Неверные координаты!\n");
        return;
    }

    if (enemyGrid[stroka][stolb] == 'X' ||
        enemyGrid[stroka][stolb] == 'O')
    {
        printf("В эту клетку уже стреляли!\n");
        return;
    }

    printf("Попал ли ты в корабль? (Д/Н): ");
    scanf(" %9s", stolbStr);

    if (strcmp(stolbStr, "Д") == 0 ||
        strcmp(stolbStr, "д") == 0)
    {
        enemyGrid[stroka][stolb] = 'X';
        printf("Попадание!\n");
    }
    else
    {
        enemyGrid[stroka][stolb] = 'O';
        printf("Промах!\n");
    }
}

void myInput(char myGrid[DLINA][SHIRINA])
{
    int stroka;
    int stolb;
    char stolbStr[10];
    char answer[10];

    printf("\nПопали ли по твоему кораблю? (Д/Н): ");
    scanf("%9s", answer);

    printf("Введите координаты: ");
    scanf("%d %9s", &stroka, stolbStr);

    stolb = getColumn(stolbStr);

    if (stroka >= 1 && stroka <= 10 &&
        stolb >= 1 && stolb <= 10)
    {
        if (myGrid[stroka][stolb] == 'X' ||
            myGrid[stroka][stolb] == 'O')
        {
            printf("В эту клетку уже записан результат!\n");
            return;
        }

        if (strcmp(answer, "Д") == 0 ||
            strcmp(answer, "д") == 0)
        {
            myGrid[stroka][stolb] = 'X';
        }
        else
        {
            myGrid[stroka][stolb] = 'O';
        }
    }
    else
    {
        printf("Неверные координаты!\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    char hitsGrid[DLINA][SHIRINA];
    char shipsGrid[DLINA][SHIRINA];

    initGrid(hitsGrid);
    initGrid(shipsGrid);

    printf("ПУСТОЕ ИГРОВОЕ ПОЛЕ:\n");
    printGrid(shipsGrid);

    ship();

    printf("НАЧИНАЕТСЯ РАССТАНОВКА КОРАБЛЕЙ!\n");
    printf("Вводите координаты каждой палубы(корабля).\n\n");

    locationship(shipsGrid);

    printf("Все корабли успешно размещены!\n\n");

    printf("Поле попаданий:\n");
    printGrid(hitsGrid);

    printf("Поле наших кораблей:\n");
    printGrid(shipsGrid);

    while (true){
        enemyInput(hitsGrid);

        printf("\nПоле противника:\n");
        printGrid(hitsGrid);

        myInput(shipsGrid);

        printf("\nПоле попаданий по твоим кораблям:\n");
        printGrid(shipsGrid);

        printf("\nПродолжаем игру!\n");
    }
    return 0;
}