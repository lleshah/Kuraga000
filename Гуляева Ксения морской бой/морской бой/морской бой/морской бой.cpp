
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define SIZE 10

struct Ship {
    int length;
    int row;
    int col;
    bool isHorizontal;
};

void initBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void placeShip(char board[SIZE][SIZE], struct Ship ship) {
    for (int i = 0; i < ship.length; i++) {
        if (ship.isHorizontal) {
            if (ship.col + i < SIZE) {
                board[ship.row][ship.col + i] = '#';
            }
        }
        else {
            if (ship.row + i < SIZE) {
                board[ship.row + i][ship.col] = '#';
            }
        }
    }
}

void printBoard(char board[SIZE][SIZE], const char* title) {
    printf("\n=== %s ===\n", title);
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Функция выстрела
void shoot(char enemyHidden[SIZE][SIZE], char playerShots[SIZE][SIZE], int row, int col) {
    // Проверка на выход за границы поля
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        printf("Ошибка: координаты вне поля!\n");
        return;
    }

    // Проверка, стреляли ли уже в эту клетку
    if (playerShots[row][col] != '.') {
        printf("Вы уже стреляли в эту клетку!\n");
        return;
    }

    // Проверка попадания
    if (enemyHidden[row][col] == '#') {
        printf("ПОПАДАНИЕ!\n");
        playerShots[row][col] = 'X';
        enemyHidden[row][col] = 'X';
    }
    else {
        printf("МИМО!\n");
        playerShots[row][col] = 'O';
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    char board1[SIZE][SIZE];      // Ваши корабли
    char board2[SIZE][SIZE];      // Поле ваших выстрелов (видимое)
    char enemyShips[SIZE][SIZE];  // Скрытое поле с кораблями соперника

    initBoard(board1);
    initBoard(board2);
    initBoard(enemyShips);

    // Для проверки добавим пару тестовых кораблей сопернику
    struct Ship enemy1 = { 3, 2, 2, true };  // Корабль длиной 3 на строке 2, столбцах 2, 3, 4
    struct Ship enemy2 = { 2, 5, 7, false }; // Корабль длиной 2 на столбце 7, строках 5, 6
    placeShip(enemyShips, enemy1);
    placeShip(enemyShips, enemy2);

    // Расстановка ваших кораблей
    int count;
    printf("Сколько кораблей добавить на 1-е поле: ");
    scanf_s("%d", &count);

    for (int i = 0; i < count; i++) {
        struct Ship ship;
        int orientation;

        printf("\nКорабль %d\n", i + 1);
        printf("Длина (1-4): ");
        scanf_s("%d", &ship.length);

        printf("Строка (0-9): ");
        scanf_s("%d", &ship.row);

        printf("Столбец (0-9): ");
        scanf_s("%d", &ship.col);

        printf("Ориентация (1 - горизонтально, 0 - вертикально): ");
        scanf_s("%d", &orientation);
        ship.isHorizontal = (orientation == 1);

        placeShip(board1, ship);
    }

    printBoard(board1, "Поле 1 (Ваши корабли)");

    // Цикл стрельбы
    int shotRow, shotCol;
    while (true) {
        printBoard(board2, "Поле 2 (Ваши выстрелы)");
        printf("\nВведите координаты выстрела (строка и столбец через пробел, или -1 для выхода): ");

        scanf_s("%d", &shotRow);
        if (shotRow == -1) {
            printf("Выход из режима стрельбы.\n");
            break;
        }
        scanf_s("%d", &shotCol);

        shoot(enemyShips, board2, shotRow, shotCol);
    }

    return 0;
}
