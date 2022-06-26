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
        '#', // KILL
        '&', // SHIP
};

#define ARROW_KEY_PRESSED 0xE0 // код необходимых клавиш
#define KEY_ENTER 13
#define KEY_UP    72
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define KEY_LEFT  75

#define TARGET '+' // прицел

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

void draw_field(eFieldInfo *, unsigned short);

void ship_generate(eFieldInfo *);

unsigned char get_target_position(unsigned char *, unsigned char *);

int main() {
    eGameState game_state = INIT; // инициализируем переменную eGameState
    unsigned char isRun = 1; // флаг "факта игры"
    int player = PLAYER_1; // чей сейчас ход?

    eFieldInfo p1_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};
    eFieldInfo p2_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};

    eFieldInfo  *tmp;

    unsigned char target_x = 0;
    unsigned char target_y = 0;
    unsigned short shot_position = 0;

    while (isRun) {
        // перебор состояний игры
        switch (game_state) {
            case INIT: {
                // инициализация игровых данных
                ship_generate(p1_data);
                ship_generate(p2_data);

                // p1_data[0] = KILL;

                game_state = DRAW;
                break;
            }
            case DRAW: {
                //system("cls"); // очистка консоли

                // отрисовка данных, зависимо от хода
                tmp = (player == PLAYER_1) ? p1_data : p2_data;
                draw_field(tmp, shot_position);

                if (get_target_position(&target_x, &target_y)) {
                    game_state = PROCESSING;
                }
                shot_position = (target_y << 8) | (target_x);
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
void draw_field(eFieldInfo *ap_data, unsigned short a_target) {
    printf("%s\n", field[0]);
    printf("%s\n", field[1]);

    unsigned char target_x = 0;
    unsigned char target_y = 0;

    target_x = a_target; // второй байт "отрезается"
    target_y = a_target >> 8; // получаем второй байт

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
            if (i == target_y && j == target_x) {
                printf("%c", TARGET);
            }
            else {
                printf(" ");
            }
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

unsigned char get_target_position(unsigned char *ap_x, unsigned char *ap_y) {
    int key = 0;
    key = getch();
    switch (key)
    {
        case ARROW_KEY_PRESSED:
        {
            switch (getch())
            {
                case KEY_DOWN:
                {
                    if (*ap_y < (FIELD_SIZE - 1)) {
                        (*ap_y)++;
                    }
                    return 0;
                }
                case KEY_UP:
                {
                    if (*ap_y > 0) {
                        (*ap_y)--;
                    }
                    return 0;
                }
                case KEY_LEFT:
                {
                    if (*ap_x > 0) {
                        (*ap_x)--;
                    }
                    return 0;
                }
                case KEY_RIGHT:
                {
                    if (*ap_x < (FIELD_SIZE - 1)) {
                        (*ap_x)++;
                    }
                    return 0;
                }
            }
        }
        case KEY_ENTER:
            return 1;
    }
    return 0;
}
