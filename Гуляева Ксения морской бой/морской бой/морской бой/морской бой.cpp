#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

const int N = 12;
const char* COLS = "АБВГДЕЖЗИК";

int getColIndex(unsigned char ch) {
    if (ch >= 224 && ch <= 255) {
        ch -= 32;
    }
    else if (ch == 184) {
        ch = 197;
    }
    for (int i = 0; i < 10; i++) {
        if ((unsigned char)COLS[i] == ch) {
            return i + 1;
        }
    }
    return -1;
}

void initBoard(char b[12][12]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            b[i][j] = (i == 0 || i == 11 || j == 0 || j == 11) ? ' ' : '.';
}

bool canPlace(char b[12][12], int r, int c, int len, int horiz) {
    for (int i = 0; i < len; i++) {
        int nr = r + (horiz ? 0 : i), nc = c + (horiz ? i : 0);
        if (nr < 1 || nr > 10 || nc < 1 || nc > 10) return false;
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++)
                if (b[nr + dr][nc + dc] == '#') return false;
    }
    return true;
}

void placeShip(char b[12][12], int r, int c, int len, int horiz) {
    for (int i = 0; i < len; i++)
        b[r + (horiz ? 0 : i)][c + (horiz ? i : 0)] = '#';
}

void autoPlace(char b[12][12]) {
    int fleet[5] = { 0, 4, 3, 2, 1 };
    for (int len = 4; len >= 1; len--) {
        int placed = 0;
        while (placed < fleet[len]) {
            int r = rand() % 10 + 1;
            int c = rand() % 10 + 1;
            int h = rand() % 2;
            if (canPlace(b, r, c, len, h)) {
                placeShip(b, r, c, len, h);
                placed++;
            }
        }
    }
}

void countShips(char b[12][12], int s[5]) {
    for (int i = 0; i < 5; i++) s[i] = 0;
    for (int r = 1; r <= 10; r++) {
        for (int c = 1; c <= 10; c++) {
            bool isShip = (b[r][c] == '#' || b[r][c] == 'X');
            bool topShip = (b[r - 1][c] == '#' || b[r - 1][c] == 'X');
            bool leftShip = (b[r][c - 1] == '#' || b[r][c - 1] == 'X');
            if (isShip && !topShip && !leftShip) {
                int len = 0;
                bool alive = false;
                int dr = (b[r + 1][c] == '#' || b[r + 1][c] == 'X') ? 1 : 0;
                int dc = (dr == 0) ? 1 : 0;
                while (b[r + len * dr][c + len * dc] == '#' || b[r + len * dr][c + len * dc] == 'X') {
                    if (b[r + len * dr][c + len * dc] == '#') alive = true;
                    len++;
                }
                if (alive && len <= 4) s[len]++;
            }
        }
    }
}

void markSunk(char real[12][12], int r, int c) {
    int r1 = r, r2 = r, c1 = c, c2 = c;
    while (real[r1 - 1][c] == '#' || real[r1 - 1][c] == 'X') r1--;
    while (real[r2 + 1][c] == '#' || real[r2 + 1][c] == 'X') r2++;
    while (real[r][c1 - 1] == '#' || real[r][c1 - 1] == 'X') c1--;
    while (real[r][c2 + 1] == '#' || real[r][c2 + 1] == 'X') c2++;
    for (int i = r1; i <= r2; i++)
        for (int j = c1; j <= c2; j++)
            if (real[i][j] == '#') return;
    for (int i = r1; i <= r2; i++) {
        for (int j = c1; j <= c2; j++) {
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = i + dr, nc = j + dc;
                    if (nr >= 1 && nr <= 10 && nc >= 1 && nc <= 10 && real[nr][nc] == '.')
                        real[nr][nc] = '0';
                }
            }
        }
    }
}

void printBoards(char p1[12][12], char p2[12][12], bool showEnemy) {
    int s1[5], s2[5];
    countShips(p1, s1);
    countShips(p2, s2);
    printf("\n          ВАШЕ ПОЛЕ                         %s\n", showEnemy ? "ПОЛЕ ПРОТИВНИКА" : "ВАШИ ВЫСТРЕЛЫ");
    printf("   А Б В Г Д Е Ж З И К               А Б В Г Д Е Ж З И К\n");
    printf("  +---------------------+           +---------------------+\n");
    for (int i = 1; i <= 10; i++) {
        printf("%2d| ", i);
        for (int j = 1; j <= 10; j++) printf("%c ", p1[i][j]);
        printf("|         %2d| ", i);
        for (int j = 1; j <= 10; j++) {
            char ch = (!showEnemy && p2[i][j] == '#') ? '.' : p2[i][j];
            printf("%c ", ch);
        }
        printf("|\n");
    }
    printf("  +---------------------+           +---------------------+\n");
    printf("Ваши корабли: [1]:%d [2]:%d [3]:%d [4]:%d\n", s1[1], s1[2], s1[3], s1[4]);
    printf("Корабли врага:[1]:%d [2]:%d [3]:%d [4]:%d\n", s2[1], s2[2], s2[3], s2[4]);
}

int countChar(char b[12][12], char target) {
    int cnt = 0;
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (b[i][j] == target) cnt++;
    return cnt;
}

bool shoot(char enemy[12][12], int r, int c) {
    if (r < 1 || r > 10 || c < 1 || c > 10 || enemy[r][c] == 'X' || enemy[r][c] == '0') {
        printf("Некорректные координаты или вы уже стреляли сюда!\n");
        return false;
    }
    if (enemy[r][c] == '#') {
        printf("ПОПАДАНИЕ!\n");
        enemy[r][c] = 'X';
        markSunk(enemy, r, c);
    }
    else {
        printf("МИМО!\n");
        enemy[r][c] = '0';
    }
    return true;
}

void botShoot(char player[12][12]) {
    while (true) {
        int r = rand() % 10 + 1, c = rand() % 10 + 1;
        if (player[r][c] == '.' || player[r][c] == '#') {
            if (player[r][c] == '#') {
                printf("Враг выстрелил в %c%d и ПОПАЛ!\n", COLS[c - 1], r);
                player[r][c] = 'X';
                markSunk(player, r, c);
            }
            else {
                printf("Враг выстрелил в %c%d и промахнулся.\n", COLS[c - 1], r);
                player[r][c] = '0';
            }
            break;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));

    char player[12][12], enemy[12][12];
    initBoard(player);
    initBoard(enemy);

    autoPlace(enemy);

    int choice;
    printf("Расстановка вашего флота (1x4, 2x3, 3x2, 4x1):\n");
    printf("1 - Расставить автоматически (рандом)\n");
    printf("2 - Расставить вручную\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    if (choice == 1) {
        autoPlace(player);
    }
    else {
        int fleetLeft[5] = { 0, 4, 3, 2, 1 };
        int totalShips = 10;
        for (int i = 0; i < totalShips; i++) {
            int len, row, horiz;
            unsigned char colCh;
            printf("\nОсталось расставить: [1]:%d [2]:%d [3]:%d [4]:%d\n", fleetLeft[1], fleetLeft[2], fleetLeft[3], fleetLeft[4]);
            printf("Корабль %d/10 (длина 1-4, координата А1..К10, ориентация 1-гор/0-верт): ", i + 1);
            scanf("%d %c%d %d", &len, &colCh, &row, &horiz);

            int col = getColIndex(colCh);
            if (len >= 1 && len <= 4 && fleetLeft[len] > 0 && col != -1 && canPlace(player, row, col, len, horiz)) {
                placeShip(player, row, col, len, horiz);
                fleetLeft[len]--;
            }
            else {
                printf("Ошибка установки! Проверьте лимит кораблей, границы или отступ в 1 клетку.\n");
                i--;
            }
        }
    }

    bool earlyExit = false;
    while (countChar(player, '#') > 0 && countChar(enemy, '#') > 0) {
        printBoards(player, enemy, false);
        unsigned char colCh;
        int row;
        printf("\nВаш выстрел (например А5, или Х для выхода): ");
        scanf(" %c", &colCh);
        if (colCh == (unsigned char)'Х' || colCh == (unsigned char)'х') {
            earlyExit = true;
            break;
        }
        scanf("%d", &row);
        int col = getColIndex(colCh);
        if (shoot(enemy, row, col) && countChar(enemy, '#') > 0) {
            botShoot(player);
        }
    }

    printf("\n=== ИТОГИ ИГРЫ ===\n");
    if (earlyExit) printf("Игра завершена досрочно.\n");
    else if (countChar(enemy, '#') == 0) printf("ПОБЕДИТЕЛЬ: ИГРОК!\n");
    else printf("ПОБЕДИТЕЛЬ: КОМПЬЮТЕР!\n");

    printf("Ваши попадания: %d | Попадания врага: %d\n", countChar(enemy, 'X'), countChar(player, 'X'));
    printBoards(player, enemy, true);

    return 0;
}
