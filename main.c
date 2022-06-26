#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // ������� ������

// ��������� ����
typedef enum {
    INIT = 0, // ������������� ������
    DRAW, // ��������� ������
    PROCESSING, // ��������� ������
    EXIT // ����� �� ����
}eGameState;

// ������� ������������
typedef enum {
    EMPTY = 0, // ������ ����
    SHOT, // ��������� �������
    STRIKE, // ������� �����
    KILL, // ������� ����
    SHIP, // ��� �������
    EFIELD_INFO_END // ������
}eFieldInfo;

// ����������� � ������������� �� ����
char draw_symbol[EFIELD_INFO_END] = {
        ' ', // EMPTY
        '*', // SHOT
        'X', // STRIKE
        '5', // KILL
        '0', // SHIP
};

#define PLAYER_1 0
#define PLAYER_2 ~PLAYER_1

#define N 13 // ���������� ����� �������� ����
#define FIELD_SIZE 10 // ���������� �������� ������ ����
#define PROBABILITY_OF_SHIP 15 // ����������� ������� �� �������

// ����� ��� �������� ����
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
    eGameState game_state = INIT; // �������������� ���������� eGameState
    unsigned char isRun = 1; // ���� "����� ����"
    int player = PLAYER_1; // ��� ������ ���?

    eFieldInfo p1_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};
    eFieldInfo p2_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};

    eFieldInfo  *tmp;

    while (isRun) {
        // ������� ��������� ����
        switch (game_state) {
            case INIT: {
                // ������������� ������� ������

                ship_generate(p1_data);
                ship_generate(p2_data);

                p1_data[0] = KILL;

                game_state = DRAW;
                break;
            }
            case DRAW: {
                //system("cls"); // ������� �������

                // ��������� ������, �������� �� ����
                tmp = (player == PLAYER_1) ? p1_data : p2_data;
                draw_field(tmp);

                game_state = PROCESSING;

                getch(); // ��� ����� ������� ������
                break;
            }
            case PROCESSING: {
                // ��������� ������� ������

                player = ~player; // ����� ����

                game_state = DRAW;
                break;
            }
            case EXIT: {
                // ����� �� ����

                break;
            }
        }
    }
    return 0;
}

// ����� �������� ����
// ����� ������ ���� ������ �� ���������� �������
// � ������� ����� � ���������� ��������
void draw_field(eFieldInfo *ap_data) {
    printf("%s\n", field[0]);
    printf("%s\n", field[1]);
    for (int i = 0; i < 10; ++i) {
        printf("%c%c", field[i + 2][0], field[i + 2][1]);

        // ���� ������ 1
        for (int j = 0; j < FIELD_SIZE; ++j) {
            printf("%c", draw_symbol[ap_data[i * FIELD_SIZE + j]]);
        }
        for (int j = 12; j < 19; ++j) {
            printf("%c", field[i + 2][j]);
        }
        // ���� ������ 2
        for (int j = 0; j < FIELD_SIZE; ++j) {
            printf(" ");
        }
        printf("%c\n", field[i + 2][29]);
    }
    printf("%s\n", field[N - 1]);
}

// ��������� �������� �� ����
void ship_generate(eFieldInfo *ap_data) {
    // ����� �� ��������� ���������� ������, � �������� i * 10 + j,
    // ��� i - ������, j - �������

    // �������� �� ���� � ������ ������� � ������������ PROBABILITY_OF_SHIP (� ���������)
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            ap_data[i * 10 + j] = (rand() % 100) <= PROBABILITY_OF_SHIP ? SHIP : EMPTY;
        }
    }
}