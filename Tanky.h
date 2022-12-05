// Tanky.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>    

#define PI 3.14159265358979323846

#define RADKY 25                /* pocet radku v hracim poli */
#define SLOUPECKY 80          /* pocet sloupecku v hracim poli */
#define START_X1 8              /* startovni souradnice tanku1 na ose X */
#define START_Y1 20             /* startovni souradnice tanku1 na ose Y */
#define START_X2 73            /* startovni souradnice tanku2 na ose X */
#define START_Y2 20             /* startovni souradnice tanku2 na ose Y */
#define START_X3 35            /* startovni souradnice tanku2 na ose X */
#define START_Y3 20             /* startovni souradnice tanku2 na ose Y */
#define pravo 1
#define levo -1

int startyX[4] = {0, START_X1, START_X2, START_X3};
int startyY[4] = {0, START_Y1, START_Y2, START_Y3};

int hraci() {
    char playersCount;
    printf("Zvolte pocet hracu: ");
    scanf("%c", &playersCount);

    switch (playersCount)
    {
    case '1':
        return 1;

    case '2':
        return 2;

    case '3':
        return 3;

    default:
        return -1;
    }
    return 0;
}

void vymaz() {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}
void gotoxy(int x, int y){
    COORD point;
    point.X = x; point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void delay(double ms) {
    clock_t End = (clock_t)(ms + clock());
    while (End > clock());
}
int MyGetch(void) {
    int Ret = getch();
    if ((!Ret || Ret == 0xE0) && kbhit())
        Ret = 256 + getch();
    return Ret;
}
void barva(int color) {
    switch (color)
    {
    case -1:    /* Cerna na Cernem */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        break;
    case 0: /* Bila na Cerne */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case 1: /* Zelena na Cerne */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
            FOREGROUND_GREEN);
        break;
    case 2: /* Zluta na Cerne */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
            FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case 3: /* Cervena na Cerne */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
            FOREGROUND_RED);
        break;
    default: /* Bila na Cerne */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
}
void RAM_ZED() {
    int i, j, hraci_pole[RADKY][SLOUPECKY];
    //Vyplni hraci pole v okrajich* 
    for (i = 0; i < 80; i++)
    {
        hraci_pole[0][i] = 1;
        hraci_pole[24][i] = 1;
    }
    for (j = 0; j < 25; j++)
    {
        hraci_pole[j][0] = 1;
        hraci_pole[j][79] = 1;
    }
    /* Vykresli zed */
    for (i = 0; i < 25; i++)
    {
        gotoxy(0, i);
        putc('|', stdout);
        gotoxy(79, i);
        putc('|', stdout);
    }
    for (i = 0; i < 80; i++) 
    {
        gotoxy(i, 0);
        putc('-', stdout);
        gotoxy(i, 24);
        putc('-', stdout);
    }
}

typedef struct Souradnice_tanku {
    int x;
    int y;
};
Souradnice_tanku* alokuj_tank(void) {
    Souradnice_tanku* sou_tan_start;
    sou_tan_start = (Souradnice_tanku*)malloc(sizeof(Souradnice_tanku));
    return sou_tan_start;
}
Souradnice_tanku* sou_tan;

void vykresli_tank_start(int tank, int life)
{
    barva(life);
    sou_tan[tank].x = startyX[tank];
    sou_tan[tank].y = startyY[tank];
    gotoxy(sou_tan[tank].x, sou_tan[tank].y);
    putc('A', stdout);
}

/*
void vykresli_tank_start2(int tank, int life)
{
    barva(life);
    sou_tan->x = START_X2;
    sou_tan->y = START_Y2;
    gotoxy(sou_tan->x, sou_tan->y);
    putc('A', stdout);
}*/

typedef struct Draha_strely
{
    int x;
    int y;
};

Draha_strely* strela;

void strelba(int vstupX, int vstupY) {
    strela = (struct Draha_strely*)malloc(sizeof(struct Draha_strely));
    int smer = 1;
    gotoxy(5, 5);
    //printf(" Kam strilis? ");

    int key = MyGetch();
    if (key) {
        int v0 = 18; char k = 0;
        double alfa = PI/4;
        int h; int i; 

        strela->x = vstupX+smer;
        strela->y = vstupY;
        h = (v0 * v0 * sin(alfa) * sin(alfa)) / (2*10);

        for (i = 0; i < h; i++) {
            barva(0); 
            gotoxy(strela->x, strela->y);
            putc(' ', stdout);
            strela->x = strela->x + i;
            strela->y = strela->y - smer;
            if (((strela->x) >= SLOUPECKY) || ((strela->y) >= RADKY)) {
                gotoxy(10, 10);
                printf("Uplne mimo!");
                getchar();
            }
            else {
                gotoxy(strela->x, strela->y);
                    putc('*', stdout);
            }
            delay(200);
        }
        gotoxy(strela->x, strela->y);
        putc(' ', stdout);
        strela->y = strela->y - smer;
        for (i =0; h >= i; h--) {
            gotoxy(strela->x, strela->y);
            putc(' ', stdout);
            strela->x = strela->x + h;
            strela->y = strela->y + smer;
            gotoxy(strela->x, strela->y); scanf("%c", k);
            if (((strela->x) >= SLOUPECKY) || ((strela->y) >= RADKY) || (k = 'x')) {
                gotoxy(10, 10);
                printf("Uplne mimo!");
                getchar();
            }
            else if((strela->x == START_X2) && (strela->y == START_Y2)) {
                vykresli_tank_start(2, 2);
                gotoxy(10, 10);
                printf("Zasahli jste pana Strika!");
                getchar();

            }else {
                barva(0); 
                gotoxy(strela->x, strela->y);
                putc('*', stdout);
            }
            delay(200);
            
        }
        /*while (strela->y != START_Y2) {
            strela->x = strela->x + (cos(alfa) * v0 * t) / 1;
            strela->y = strela->y - ((sin(alfa) * v0* t)+((1/2)*(-0,1)*t)) / 1;
            gotoxy(strela->x, strela->y);
            putc('*', stdout);
            t++; delay(1000);
        }*/ 
    }
}
 
void zivoty(int pocethracu) {
    for (int i = 1; i <= pocethracu; i++) {



    }
}
