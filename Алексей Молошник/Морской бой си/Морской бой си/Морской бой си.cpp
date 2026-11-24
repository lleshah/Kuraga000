#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <clocale>
#include <windows.h>


const int DLINA = 12;
const int SHIRINA = 12;

void printGrid(char grid[DLINA][SHIRINA])
{
	printf("     А Б В Г Д Е Ё Ж З И \n");
	for (int i = 0; i < DLINA; i++)
	{
		if (i >= 1 && i <= 10)
		{
			printf("%2d ", i);
		}
		else {
			printf("   ");
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
			if (i == 0 || i == DLINA - 1 || j == 0 || j == SHIRINA - 1)
			{
				grid[i][j] = '#';
			}
			else {
				grid[i][j] = '.';
			}
		}
	}
}

bool input(char hitsGrid[DLINA][SHIRINA], char shipsGrid[DLINA][SHIRINA])
{
    int stroka;
    char stolbStr[10]; 
    int stolb = 0;
    char nomber;

    printf("Введите строку и столбец (букву от А до И) или 0 для выхода: ");
    scanf("%d", &stroka);
    if (stroka == 0)
    {
        return false;
    }

    scanf("%9s", stolbStr);
    if (strcmp(stolbStr, "А") == 0) {
        stolb = 1;
    }
    else if (strcmp(stolbStr, "Б") == 0) {
        stolb = 2;
    }
    else if (strcmp(stolbStr, "В") == 0) {
        stolb = 3;
    }
    else if (strcmp(stolbStr, "Г") == 0) {
        stolb = 4;
    }
    else if (strcmp(stolbStr, "Д") == 0) {
        stolb = 5;
    }
    else if (strcmp(stolbStr, "Е") == 0) {
        stolb = 6;
    }
    else if (strcmp(stolbStr, "Ё") == 0) {
        stolb = 7;
    }
    else if (strcmp(stolbStr, "Ж") == 0) {
        stolb = 8;
    }
    else if (strcmp(stolbStr, "З") == 0) {
        stolb = 9;
    }
    else if (strcmp(stolbStr, "И") == 0) {
        stolb = 10;
    }
    else {
        printf("Такой буквы нет в диапазоне от А до И!\n");
        return true; 
    }

    if (stroka >= 1 && stroka <= DLINA && stolb >= 1 && stolb <= SHIRINA)
    {
        if (shipsGrid[stroka - 1][stolb - 1] == 'K')
        {
            nomber = 'X';
            printf("Попадание!\n");
        }
        else {
            nomber = 'O';
            printf("Промах!\n");
        }
        hitsGrid[stroka - 1][stolb - 1] = nomber;
        return true;
    }
    else {
        printf("Неверные координаты!\n");
        return true;
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


	shipsGrid[2][2] = 'K';
	shipsGrid[2][3] = 'K';
	shipsGrid[2][4] = 'K';
	shipsGrid[4][5] = 'K';
	shipsGrid[5][5] = 'K';
	shipsGrid[7][7] = 'K';

	printf("Поле попаданий:\n");
	printGrid(hitsGrid);

	printf("Поле наших кораблей:\n");
	printGrid(shipsGrid);

	while (input(hitsGrid, shipsGrid))
	{
		printf("Поле попаданий:\n");
		printGrid(hitsGrid);

		printf("Поле наших кораблей:\n");
		printGrid(shipsGrid);
	}
	return 0;
}