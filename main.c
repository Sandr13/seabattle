#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // нажатие клавиш

// состояния игры
typedef enum {
    INIT = 0, // инициализация данных
    DRAW, // отрисовка данных
    PROCESSING, // обработка данных
    EXIT // выход из игры
}eGameState;

// объявим перечисления
typedef enum {
    EMPTY = 0, // пустое поле
    SHOT, // произведён выстрел
    STRIKE, // корабль ранен
    KILL, // корабль убит
    SHIP, // сам корабль
    EFIELD_INFO_END // размер
}eFieldInfo;

// определимся с обозначениями на поле
char draw_symbol[EFIELD_INFO_END] = {
        ' ', // EMPTY
        '*', // SHOT
        'X', // STRIKE
        '5', // KILL
        '0', // SHIP
};

#define PLAYER_1 0
#define PLAYER_2 ~PLAYER_1

#define N 13 // количество строк игрового поля
#define FIELD_SIZE 10 // количество символов внутри поля
#define PROBABILITY_OF_SHIP 15 // вероятность корабля на позиции

// задаём вид игрового поля
char *field[] = {
       "  ABCDEFGHIJ       ABCDEFGHIJ ",
       " *----------*     *----------*",
       "0|          |    0|          |",
       "1|          |    1|          |",
       "2|          |    2|          |",
       "3|          |    3|          |",
       "4|          |    4|          |",
       "5|          |    5|          |",
       "6|          |    6|          |",
       "7|          |    7|          |",
       "8|          |    8|          |",
       "9|          |    9|          |",
       " *----------*     *----------*"
};

void draw_field(eFieldInfo *);

void ship_generate(eFieldInfo *);

int main() {
    eGameState game_state = INIT; // инициализируем переменную eGameState
    unsigned char isRun = 1; // флаг "факта игры"
    int player = PLAYER_1; // чей сейчас ход?

    eFieldInfo p1_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};
    eFieldInfo p2_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};

    eFieldInfo  *tmp;

    while (isRun) {
        // перебор состояний игры
        switch (game_state) {
            case INIT: {
                // инициализация игровых данных

                ship_generate(p1_data);
                ship_generate(p2_data);

                p1_data[0] = KILL;

                game_state = DRAW;
                break;
            }
            case DRAW: {
                //system("cls"); // очистка консоли

                // отрисовка данных, зависимо от хода
                tmp = (player == PLAYER_1) ? p1_data : p2_data;
                draw_field(tmp);

                game_state = PROCESSING;

                getch(); // ждём любое нажатие клавиш
                break;
            }
            case PROCESSING: {
                // обработка игровых данных

                player = ~player; // смена хода

                game_state = DRAW;
                break;
            }
            case EXIT: {
                // выход из игры

                break;
            }
        }
    }
    return 0;
}

// вывод игрового поля
// вывод внутри поля берётся из отдельного массива
// с которым будем в дальнейшем работать
void draw_field(eFieldInfo *ap_data) {
    printf("%s\n", field[0]);
    printf("%s\n", field[1]);
    for (int i = 0; i < 10; ++i) {
        printf("%c%c", field[i + 2][0], field[i + 2][1]);

        // поле игрока 1
        for (int j = 0; j < FIELD_SIZE; ++j) {
            printf("%c", draw_symbol[ap_data[i * FIELD_SIZE + j]]);
        }
        for (int j = 12; j < 19; ++j) {
            printf("%c", field[i + 2][j]);
        }
        // поле игрока 2
        for (int j = 0; j < FIELD_SIZE; ++j) {
            printf(" ");
        }
        printf("%c\n", field[i + 2][29]);
    }
    printf("%s\n", field[N - 1]);
}

// генерация кораблей на поле
void ship_generate(eFieldInfo *ap_data) {
    // здесь мы принимаем одномерный массив, с индексом i * 10 + j,
    // где i - строка, j - столбец

    // проходим всё поле и ставим корабль с вероятностью PROBABILITY_OF_SHIP (в процентах)
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            ap_data[i * 10 + j] = (rand() % 100) <= PROBABILITY_OF_SHIP ? SHIP : EMPTY;
        }
    }
}