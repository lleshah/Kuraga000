#include <iostream>
#include <Windows.h>

int main()
const int A = 20;
const int B = 20;

// 1. Создать и заполнить массив точками
char tabl[A][B];
for (int i = 0; i < A; i++) {
    for (int j = 0; j < B; j++) {
        tabl[i][j] = '.';
    }
}

// Цикл программы для постоянного ввода данных
while (true) {
    // Верхняя граница (добавлен правильный шаг пробелов)
    for (int j = 0; j < B + 2; j++) {
        printf("#\n");
    }

    // Строки массива и боковые стены
    for (int i = 0; i < A; i++) {
        printf("#\n"); // Тут левая стена
        for (int j = 0; j < B; j++) {
            tabl[i][j]; // Выводим точку 
            printf("#\n"); // Тут правая стена
        }

        // Нижняя граница
        for (int j = 0; j < B + 2; j++) {
            printf("#\n");
        }


        // 3. Запрос данных у пользователя
        int user_row, user_col;
        char user_char;

        printf("Введите номер строки (1-" << A << "), столбца (1-" << B << ") и символ через пробел:\n");
        cin >> user_row >> user_col >> user_char;

        // Переводим из привычных пользователю координат (от 1) в индексы массива (от 0)
        int index_row = user_row - 1;
        int index_col = user_col - 1;

        // 4. Проверка: лежат ли введенные координаты внутри границ массива
        if (index_row >= 0 && index_row < A && index_col >= 0 && index_col < B) {
            tabl[index_row][index_col] = user_char;
            printf("Массив успешно обновлен!\n");
        }
        else {
            printf("[Ошибка] Вы вышли за границы массива! Попробуйте снова.\n");
        }
    }

    return 0;
}
