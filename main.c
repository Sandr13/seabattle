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
        '#', // KILL
        '&', // SHIP

};

#define N 13 // ���������� ����� �������� ����
#define FIELD_SIZE 10 // ���������� �������� ������ ����

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

void draw_field();

void ship_generate(eFieldInfo *);

int main() {
    eGameState game_state = INIT; // �������������� ���������� eGameState
    unsigned char isRun = 1; // ���� "����� ����"

    eFieldInfo p1_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};
    eFieldInfo p2_data[FIELD_SIZE * FIELD_SIZE] = {EMPTY};

    while (isRun) {
        // ������� ��������� ����
        switch (game_state) {
            case INIT: {
                // ������������� ������� ������

                ship_generate(p1_data);
                ship_generate(p2_data);

                game_state = DRAW;
                break;
            }
            case DRAW: {
                system("cls"); // ������� �������

                // ��������� ������
                draw_field();

                game_state = PROCESSING;

                getch(); // ��� ����� ������� ������
                break;
            }
            case PROCESSING: {
                // ��������� ������� ������
                game_state = DRAW;
                break;
            }
            case EXIT: {
                // ����� �� ����

                break;
            }
        }
    }

    draw_field();

    // printf("%c\n", draw_symbol[KILL]);
    // printf("%c\n", draw_symbol[SHIP]);

    return 0;
}

// ����� �������� ����
// ����� ������ ���� ������ �� ���������� �������
// � ������� ����� � ���������� ��������
void draw_field() {
    printf("%s\n", field[0]);
    printf("%s\n", field[1]);
    for (int i = 0; i < 10; ++i) {
        printf("%c%c", field[i + 2][0], field[i + 2][1]);

        for (int j = 0; j < FIELD_SIZE; ++j) {
            printf(" ");
        }
        for (int j = 12; j < 19; ++j) {
            printf("%c", field[i + 2][j]);
        }
        for (int j = 0; j < FIELD_SIZE; ++j) {
            printf(" ");
        }
        printf("%c\n", field[i + 2][29]);
    }
    printf("%s\n", field[N - 1]);
}

// ��������� �������� �� ����
void ship_generate(eFieldInfo *ap_data) {
    // �������� ��������
    
}