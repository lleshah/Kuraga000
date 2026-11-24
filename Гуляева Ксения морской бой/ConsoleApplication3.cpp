#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

const int H = 20;
const int W = 20;

void clearConsole() {
    system("cls");
}

void drawBox(char box[H][W], bool smooth) {
    clearConsole();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c ", box[i][j]);
            if (smooth) {
                fflush(stdout);
                this_thread::sleep_for(chrono::milliseconds(10));
            }
        }
        printf("\n");
    }
}

int main() {
    char box[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            box[i][j] = ' ';
        }
    }

    for (int j = 1; j < W - 1; j++) {
        box[0][j] = '_';
        box[H - 1][j] = '_';
    }

    for (int i = 1; i < H - 1; i++) {
        box[i][0] = '|';
        box[i][W - 1] = '|';
    }

    drawBox(box, true);

    int row, col;
    char num;
    while (true) {
        printf("Vvedite stroku (0-%d), stolbec (0-%d) i cifru: ", H - 1, W - 1);
        scanf_s("%d %d %c", &row, &col, &num, 1);

        if (row >= 0 && row < H && col >= 0 && col < W) {
            box[row][col] = num;
            drawBox(box, false);
        }
        else {
            printf("Nevernye koordinaty!\n");
        }
    }
    return 0;
}
