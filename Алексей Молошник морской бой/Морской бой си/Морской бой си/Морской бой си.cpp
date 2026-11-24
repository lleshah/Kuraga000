#include <cstdio>
#include <clocale>
#include <windows.h>

const int DLINA = 30;
const int SHIRINA = 30;

void printGrid(char grid[DLINA][SHIRINA]) {
    for (int i = 0; i < DLINA; i++) {
        for (int j = 0; j < SHIRINA; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void initGrid(char grid[DLINA][DLINA]) {
    for (int i = 0; i < DLINA; i++) {
        for (int j = 0; j < SHIRINA; j++) {
            if (i == 0 || i == DLINA - 1 || j == 0 || j == SHIRINA - 1) {
                grid[i][j] = '#';
            }
            else {
                grid[i][j] = '.';
            }
        }
    }
}

bool input(char grid[DLINA][SHIRINA]) {
    int stroka, stolb;
    char nomber;
    printf("Введите строку, столбец и цифру (или 0 для выходаm из системы): ");
    scanf("%d", &stroka);
    if (stroka == 0) {
        return false;
    }
    scanf("%d %c", &stolb, &nomber);
    if (stroka >= 2 && stroka <= SHIRINA - 1 && stolb >= 1 && stolb <= DLINA - 1 && nomber >= '1' && nomber <= '9') {
        grid[stroka - 1][stolb - 1] = nomber;
        return true;
    }
    else {
        printf("Неправильно ввёл числа!\n");
        exit(0);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char grid[DLINA][SHIRINA];
    initGrid(grid);

    printf("Исходный массив:\n");
    printGrid(grid);

    while (input(grid)) {
        printf("Следующий массив:\n");
        printGrid(grid);
    }
    return 0;
}