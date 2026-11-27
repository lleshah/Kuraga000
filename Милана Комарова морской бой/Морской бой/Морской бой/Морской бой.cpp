#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <clocale>
#include <windows.h>


const int DLINA = 12;
const int SHIRINA = 12;

void printGrid(char massiv[DLINA][SHIRINA]) {
	printf("        А Б В Г Д Е Ж З И К \n");

	for (int i = 0; i < DLINA; i++)
	{
		if (i == 0 || i == DLINA - 1) {
			printf("    | ");
		}
		else {
			printf(" %2d | ", i);
		}

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

bool input(char hitsGrid[DLINA][SHIRINA], char shipsGrid[DLINA][SHIRINA]) {
	int stroka = -1;
	char stolb_char;
	int stolb = -1;

	printf("Введите координаты (например, 2А или 5Б), для выхода введите 0: ");
	int res = scanf("%d%c", &stroka, &stolb_char);

	if (stroka == 0)

		return false;

		if (res != 2) {
		printf("Неверный формат! Пишите число и букву вместе, например: 2А\n");
		while (getchar() != '\n');
		return true;
	}
		if (stolb_char >= 'а' && stolb_char <= 'я') {
			stolb_char = stolb_char - 'а' + 'А';
		}
		if (stolb_char >= 'А' && stolb_char <= 'И') {
			stolb = stolb_char - 'А' + 1;
		} else if (stolb_char == 'К') {
			stolb = 10;
		}
		if (stroka >= 1 && stroka <= 10 && stolb != -1) {
			if (shipsGrid[stroka][stolb] == 'K') {
				hitsGrid[stroka][stolb] = 'X';
				printf("Попадание!\n");
			}
			else {
				hitsGrid[stroka][stolb] = 'O';
				printf("Промах!\n");
			}
		}
		else {
			printf("Неправильно ввёл координаты! Попробуйте еще одну попытку.\n");
		}

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
	shipsGrid[2][5] = 'K';
	shipsGrid[5][5] = 'K';
	shipsGrid[5][6] = 'K';
	shipsGrid[5][7] = 'K';
	shipsGrid[7][3] = 'K';
	shipsGrid[8][3] = 'K';
	shipsGrid[1][9] = 'K';
	shipsGrid[7][5] = 'K';
	shipsGrid[9][7] = 'K';
	shipsGrid[3][9] = 'K';
	shipsGrid[8][10] = 'K';
	shipsGrid[7][10] = 'K';
	shipsGrid[5][1] = 'K';
	shipsGrid[5][2] = 'K';
	shipsGrid[8][1] = 'K';
	shipsGrid[9][1] = 'K';
	shipsGrid[7][1] = 'K';

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