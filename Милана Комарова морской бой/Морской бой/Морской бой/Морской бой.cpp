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
			printf("    * ");
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
	bool my_turn = true;
	while (my_turn) {
		int stroka = -1;
		char stolb_char;
		int stolb = -1;

		printf("Сейчас твой ход! Введите координаты вашего выстрела: ");
		int res = scanf("%d%c", &stroka, &stolb_char);

		if (stroka == 0) return false;

		if (res != 2) {
			printf("Неверный формат! Ход пропущен, попробуйте в следующий раз.\n");
			while (getchar() != '\n');
			my_turn = false;
		}
		else {
			if (stolb_char >= 'а' && stolb_char <= 'я') stolb_char = stolb_char - 'а' + 'А';
			if (stolb_char >= 'А' && stolb_char <= 'И') stolb = stolb_char - 'А' + 1;
			else if (stolb_char == 'К') stolb = 10;

			if (stroka >= 1 && stroka <= 10 && stolb != -1) {
				while (getchar() != '\n');
				char otvet;
				printf("Ты попал по короблю соперника? Введи 'п'(попала) или 'м'(мимо): ");
				scanf("%c", &otvet);

				if (otvet == 'п' || otvet == 'П') {
					hitsGrid[stroka][stolb] = 'X';
					printf("Попадание! Стреляй еще раз.\n");
				}
				else {
					hitsGrid[stroka][stolb] = 'O';
					printf("Промах! Попробуй повторить попытку позже.\n");
					my_turn = false;
				}
			}
			else {
				printf("Неправильно ввела координаты! Ход пропущен.\n");
				my_turn = false;
			}
		}

		while (getchar() != '\n');

		printf("Нажмите Enter, чтобы продолжить игру.");
		getchar();

		system("cls");
		printf("Поле попаданий:\n");
		printGrid(hitsGrid);
		printf("Поле наших кораблей:\n");
		printGrid(shipsGrid);
	}

	bool enemy_turn = true;
	while (enemy_turn) {
		int vr_stroka = -1;
		char vr_stolb_char;
		int vr_stolb = -1;

		printf("Сейчас ход соперника! Введите координаты выстрела соперника: ");
		int vr_res = scanf("%d%c", &vr_stroka, &vr_stolb_char);

		if (vr_stroka == 0) return false;

		if (vr_res != 2) {
			printf("Неверный формат! Ход пропущен.\n");
			while (getchar() != '\n');
			enemy_turn = false;
		}
		else {
			if (vr_stolb_char >= 'а' && vr_stolb_char <= 'я') vr_stolb_char = vr_stolb_char - 'а' + 'А';
			if (vr_stolb_char >= 'А' && vr_stolb_char <= 'И') vr_stolb = vr_stolb_char - 'А' + 1;
			else if (vr_stolb_char == 'К') vr_stolb = 10;

			if (vr_stroka >= 1 && vr_stroka <= 10 && vr_stolb != -1) {
				if (shipsGrid[vr_stroka][vr_stolb] == 'K') {
					shipsGrid[vr_stroka][vr_stolb] = 'X';
					printf("Соперник попал по твоему кораблю! Он ходит снова.\n");

					while (getchar() != '\n');
					printf("Нажмите Enter, чтобы продолжить игру.");
					getchar();

					system("cls");
					printf("Поле попаданий:\n");
					printGrid(hitsGrid);
					printf("Поле наших кораблей:\n");
					printGrid(shipsGrid);
				}
				else {
					if (shipsGrid[vr_stroka][vr_stolb] != 'X') {
						shipsGrid[vr_stroka][vr_stolb] = 'O';
					}
					printf("Соперник промахнулся!\n");
					enemy_turn = false;
				}
			}
			else {
				printf("Неправильно ввела координаты соперника! Ход пропущен.\n");
				enemy_turn = false;
			}
		}
	}

	while (getchar() != '\n');
	printf("Нажмите Enter, чтобы продолжить игру.");
	getchar();
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


	// 4-палубный
	shipsGrid[2][2] = 'K';
	shipsGrid[2][3] = 'K';
	shipsGrid[2][4] = 'K';
	shipsGrid[2][5] = 'K';

	// 3-палубные
	shipsGrid[5][1] = 'K';
	shipsGrid[6][1] = 'K';
	shipsGrid[7][1] = 'K';

	shipsGrid[9][4] = 'K';
	shipsGrid[9][5] = 'K';
	shipsGrid[9][6] = 'K';

	// 2-палубные
	shipsGrid[4][4] = 'K';
	shipsGrid[4][5] = 'K';

	shipsGrid[7][8] = 'K';
	shipsGrid[8][8] = 'K';

	shipsGrid[1][9] = 'K';
	shipsGrid[1][10] = 'K';

	// 1-палубные
	shipsGrid[10][1] = 'K';
	shipsGrid[4][10] = 'K';
	shipsGrid[7][4] = 'K';
	shipsGrid[10][10] = 'K';

	printf("Поле попаданий:\n");
	printGrid(hitsGrid);

	printf("Поле наших кораблей:\n");
	printGrid(shipsGrid);

	while (input(hitsGrid, shipsGrid))
	{
		system("cls");

		printf("Поле попаданий:\n");
		printGrid(hitsGrid);

		printf("Поле наших кораблей:\n");
		printGrid(shipsGrid);
	}
	return 0;
}