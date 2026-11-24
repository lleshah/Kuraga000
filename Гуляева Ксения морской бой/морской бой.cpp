#include <stdio.h>
#include <stdbool.h>

const int SIZE = 10;

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

int main() {
    char board1[SIZE][SIZE];
    char board2[SIZE][SIZE]; // Второй массив

    initBoard(board1);
    initBoard(board2);   //Это вызов функции инициализации для двух разных игровых или вычислительных досок 

    int count;
    printf("Skolko korabley dobavit na 1-e pole: ");
    scanf_s("%d", &count);

    for (int i = 0; i < count; i++) {
        struct Ship ship;
        int orientation;

        printf("\nKorabl %d\n", i + 1);
        printf("Dlina (1-4): ");
        scanf_s("%d", &ship.length);

        printf("Stroka (0-9): ");
        scanf_s("%d", &ship.row);

        printf("Stolbec (0-9): ");
        scanf_s("%d", &ship.col);

        printf("Orientaciya (1 - gorizontalno, 0 - vertikalno): ");
        scanf_s("%d", &orientation);
        ship.isHorizontal = (orientation == 1);

        placeShip(board1, ship);
    }

   
    printBoard(board1, "Pole 1 (Vashi korabli)");
    printBoard(board2, "Pole 2 (Vystrely / Sopernik)");

    return 0;
}
