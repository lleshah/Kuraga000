#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <clocale>
#include <windows.h>


const int DLINA = 12;
const int SHIRINA = 12;

void printGrid(char massiv[DLINA][SHIRINA]) {
	printf("    А Б В Г Д Е Ж З И К \n");

	for (int i = 0; i < DLINA; i++)
	{
		printf(" %d | ", i);

		for (int j = 0; j < SHIRINA; j++)
		{
			printf("%c ", massiv[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void initGrid(char massiv[DLINA][SHIRINA])
{
	for (int i = 0; i < DLINA; i++)
	{
		for (int j = 0; j < SHIRINA; j++)
		{
			if (i == 0 || i == DLINA - 1 || j == 0 || j == SHIRINA - 1)
			{
				massiv[i][j] = '#';
			}
			else {
				massiv[i][j] = '.';
			}
		}
	}
}

bool input(char hitsGrid[DLINA][SHIRINA], char shipsGrid[DLINA][SHIRINA])
{
	int stroka, stolb;
	char nomber;
	printf("Введите строку и столбец для выхода: ");
	scanf("%d", &stroka);
	if (stroka == 0)
	{
		return false;

	}
	scanf("%d", &stolb);
	if (stroka >= 1 && stroka <= SHIRINA - 2 && stolb >= 1 && stolb <= DLINA - 2)
	{
		if (shipsGrid[stroka][stolb] == 'K')
		{
			nomber = 'X';
			printf("Попадание!\n");
		}
		else {
			nomber = 'O';
			printf("Промах!\n");
		}
		hitsGrid[stroka][stolb] = nomber;
		return true;
	}
	else {
		printf("Неправильно ввёл числа!\n");
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