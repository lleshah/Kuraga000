#include <iostream>
using namespace std;

void clearConsole() {
    system("cls");
}

int main() {
    const int H = 5;
    const int W = 7;
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

    clearConsole();

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << box[i][j];
        }
        cout << endl;
    }

    return 0;
}

