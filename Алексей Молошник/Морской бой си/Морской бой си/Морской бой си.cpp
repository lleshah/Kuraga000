#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <clocale>
#include <cstring>
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
void ship() {
    printf("ВИДЫ КОРАБЛЕЙ И ИХ КОЛИЧЕСТВО:\n");
    printf("П - 4\nПП - 3\nППП - 2\nПППП - 1\n\n");
}
void locationship(char shipsGrid[DLINA][SHIRINA]) {
    int stroka;
    char stolbStr[10];
    int stolb = 0;
    printf("Введите координаты для всех однопалубных кораблей (П): ")
        for (int i = 1, i <= 4, i++) {
            printf("Корабль %d (строка и буква): ", i);
            scanf("%d %9s", &stroka, stolbStr);
            scanf("%9s", stolbStr);
            if (strcmp(stolbStr, "А") == 0) {
                stolb = 2;
            }
            else if (strcmp(stolbStr, "Б") == 0) {
                stolb = 3;
            }
            else if (strcmp(stolbStr, "В") == 0) {
                stolb = 4;
            }
            else if (strcmp(stolbStr, "Г") == 0) {
                stolb = 5;
            }
            else if (strcmp(stolbStr, "Д") == 0) {
                stolb = 6;
            }
            else if (strcmp(stolbStr, "Е") == 0) {
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
            else if (strcmp(stolbStr, "К") == 0) {
                stolb = 11;
            }
            else {
                printf("Такой буквы нет в поле от А до К!\n");
                stolb = 0;
            if (stroka >= 1 && stroka <= 10 && stolb >= 1 && stolb <= 10 && shipsGrid[stroka][stolb] == '.')
            {
                shipsGrid[stroka][stolb] = 'П';
            }
            else {
                printf("Ошибка! Неверные координаты или клетка занята. Повторите ввод.\n");
                i--; 
             }
            }
            printf("\n");
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
        stolb = 2;
    }
    else if (strcmp(stolbStr, "Б") == 0) {
        stolb = 3;
    }
    else if (strcmp(stolbStr, "В") == 0) {
        stolb = 4;
    }
    else if (strcmp(stolbStr, "Г") == 0) {
        stolb = 5;
    }
    else if (strcmp(stolbStr, "Д") == 0) {
        stolb = 6;
    }
    else if (strcmp(stolbStr, "Е") == 0) {
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
    else if (strcmp(stolbStr, "К") == 0) {
        stolb = 11;
    }
    else {
        printf("Такой буквы нет в поле от А до К!\n");
        return true;
    }

    if (stroka >= 2 && stroka <= 10 && stolb >= 2 && stolb <= 11)
    {
        if (shipsGrid[stroka ][stolb ] == 'П')
        {
            nomber = 'X';
            printf("Попадание!\n");
        }
        else {
            nomber = 'O';
            printf("Промах!\n");
        }
        hitsGrid[stroka ][stolb ] = nomber;
        return true;
    }
    else {
        printf("Неверные координаты!\n");
        return true;
    }
}
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	char hitsGrid[DLINA][SHIRINA];
	char shipsGrid[DLINA][SHIRINA];
    ship();
	initGrid(hitsGrid);
	initGrid(shipsGrid);


	shipsGrid[2][2] = 'П';
	shipsGrid[2][3] = 'П';
	shipsGrid[2][4] = 'П';
	shipsGrid[4][5] = 'П';
	shipsGrid[5][5] = 'П';
	shipsGrid[7][7] = 'П';
    shipsGrid[9][2] = 'П';
    shipsGrid[9][3] = 'П';
    shipsGrid[9][4] = 'П';
    shipsGrid[9][5] = 'П';
    shipsGrid[9][2] = 'П';
    shipsGrid[10][10] = 'П';

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