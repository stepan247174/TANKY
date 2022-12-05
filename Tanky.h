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


#define DELKA_JMENA 21

struct tancik
{
    char  jmeno_hrace[DELKA_JMENA];
    int index;
    int zasahy;
};

void add(char* jmeno_hrace, int index);
struct tancik* hraci = (struct tancik*)malloc(sizeof(struct tancik));  // alokace dynamicke promenne

#define PI 3.14159265358979323846

#define RADKY 25                // pocet radku v hracim poli 
#define SLOUPECKY 80           // pocet sloupecku v hracim poli 
#define START_X1 8            // startovni souradnice tanku1 na ose X 
#define START_Y1 20          // startovni souradnice tanku1 na ose Y 
#define START_X2 73         // startovni souradnice tanku2 na ose X 
#define START_Y2 20        // startovni souradnice tanku2 na ose Y 
#define START_X3 35       // startovni souradnice tanku2 na ose X 
#define START_Y3 13      // startovni souradnice tanku2 na ose Y 
#define pravo 1
#define levo -1

int startyX[4] = {0, START_X1, START_X2, START_X3};
int startyY[4] = {0, START_Y1, START_Y2, START_Y3};

int hrac() {
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



void add(char* jmeno_hraca, int index)
{
    strcpy_s(hraci[index].jmeno_hrace, DELKA_JMENA, jmeno_hraca); // naplneni struktury
    hraci[index].index = index;
    hraci[index].zasahy = 0;
}

void OnAdd(int ph)
{
    int kolik = ph;
    char my_name[DELKA_JMENA];

    for (int o = 1; o <= kolik; o++) {
        printf("\nJmeno hrace %d: ", o);         // dotazeme se na polozky
        scanf_s("%s", my_name, DELKA_JMENA);
        while (getchar() != '\n');
        add(my_name, o);
    }
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
/*
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
    // Vykresli zed 
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
}*/
void RAM_ZED() {
    int i, j, hraci_pole[RADKY][SLOUPECKY];
    //Vyplni hraci pole v okrajich* 
    FILE* f = fopen("C:\\Users\\NB\\source\\repos\\Tanky\\gameboard.txt", "r");
    char c = 'c';
    if (f) {
        while ((c = fgetc(f)) != EOF) {
            printf("%c", c);
        }
    }
    fclose(f);
}
void VypisJmena(int ph) {
    barva(0);
    for (int v = 1; v <= ph; v++) {
        gotoxy(5, (v+26));
        printf("%d. hrac - %s - %dx dostal", hraci[v].index, hraci[v].jmeno_hrace, hraci[v].zasahy);
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

void vykresli_tank_mrtvej(int tank, int life)
{
    barva(life);
    sou_tan[tank].x = startyX[tank];
    sou_tan[tank].y = startyY[tank];
    gotoxy(sou_tan[tank].x, sou_tan[tank].y);
    putc('*', stdout);
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
    int v0a;
};
Draha_strely* strela = (struct Draha_strely*)malloc(sizeof(struct Draha_strely));

int JakyTank(int kdo) {
    
        if (kdo == 1) {
            return 1;
        }
        if (kdo == 2) {
            return -1;
        }
        if ((kdo == 3) || ((kdo%6)==0)) {
            return 1;
        }
        else { 
            return-1;
        }
    

}


void strelba(int vstupX, int vstupY, int smerstrely, int jakmoc) {

    int smer = smerstrely;
    int key = MyGetch();
    if (key) {
        int v0 = jakmoc; char k = 0; int kontrolazeme;
        double alfa = PI / 4;
        int h; int i; //char baf[300]; int w = 1;

        strela->x = vstupX + smer;
        strela->y = vstupY;
        h = (v0 * v0 * sin(alfa) * sin(alfa)) / (2 * 10);

        for (i = 0; i < h; i++) {             //NAHORU
            barva(0);
            gotoxy(strela->x, strela->y);
            putc(' ', stdout);
            strela->x = strela->x + i * smer;
            strela->y = strela->y - 1;
           // gotoxy(strela->x, strela->y);
           // scanf("%c", &baf[w]);
            if (((strela->x) >= SLOUPECKY) || ((strela->y) >= RADKY) || ((strela->x) <= 0) || ((strela->y) <= 0)) {
                gotoxy(10, 10);
                printf("Uplne mimo!");
                delay(3000);
                gotoxy(10, 10);
                printf("             ");
                break;
            }
            else if ((strela->x == START_X2) && (strela->y == START_Y2)) {
                hraci[2].zasahy++;
                vykresli_tank_start(2, hraci[2].zasahy + 1);
                gotoxy(10, 10);
                printf("%s dostal bidu!", hraci[2].jmeno_hrace);
                delay(2000);
                gotoxy(10, 10);
                printf("                           ");
                break;

            }
            else if ((strela->x == START_X1) && (strela->y == START_Y1)) {
                hraci[1].zasahy++;
                vykresli_tank_start(1, hraci[1].zasahy + 1);
                gotoxy(10, 10);
                printf("%s dostal bidu!", hraci[1].jmeno_hrace);
                delay(2000);
                gotoxy(10, 10);
                printf("                           ");
                break;

            }
            else if ((strela->x == START_X3) && (strela->y == START_Y3)) {
                hraci[3].zasahy++;
                vykresli_tank_start(3, hraci[3].zasahy + 1);
                gotoxy(10, 10);
                printf("%s dostal bidu!", hraci[3].jmeno_hrace);
                delay(2000);
                gotoxy(10, 10);
                printf("                           ");
                break;

            }
           /* else if (baf[w] == 'x') {
                gotoxy(10, 10);
                printf("Vedle!");
                delay(3000);
                gotoxy(10, 10);
                printf("             ");
                break;
            }*/
            else {
                gotoxy(strela->x, strela->y);
                putc('*', stdout);
            }
            delay(200);
        }

        gotoxy(strela->x, strela->y);
        putc(' ', stdout);
        if(smer == 1 ) {
        strela->y = strela->y - smer;
        }
        else 
        { strela->y = strela->y + smer;}

        for (i = 0; h >= i; h--) {                           //DOLU
            gotoxy(strela->x, strela->y);
            putc(' ', stdout);
            strela->x = strela->x + h * smer;
            strela->y = strela->y + 1;
            //gotoxy(strela->x, strela->y);
            //scanf("%c", &baf[k]);
            if (((strela->x) >= SLOUPECKY) || ((strela->y) >= RADKY) || ((strela->x) <= 0) || ((strela->y) <= 0)) {
                gotoxy(10, 10);
                printf("Uplne mimo!");
                delay(3000);
                gotoxy(10, 10);
                printf("             ");
                break;
            }
            else if ((strela->x == START_X2) && (strela->y == START_Y2)) {
                hraci[2].zasahy++;
                vykresli_tank_start(2, hraci[2].zasahy + 1);
                gotoxy(10, 10);
                printf("%s dostal bidu!", hraci[2].jmeno_hrace);
                delay(2000);
                gotoxy(10, 10);
                printf("                           ");
                break;
               
            } 
            else if ((strela->x == START_X1) && (strela->y == START_Y1)) {
                hraci[1].zasahy++;
                vykresli_tank_start(1, hraci[1].zasahy + 1);
                gotoxy(10, 10);
                printf("%s dostal bidu!", hraci[1].jmeno_hrace);
                delay(2000);
                gotoxy(10, 10);
                printf("                           ");
                break;
                
            }
            else if ((strela->x == START_X3) && (strela->y == START_Y3)) {
                hraci[3].zasahy++;
                vykresli_tank_start(3, hraci[3].zasahy + 1);
                gotoxy(10, 10);
                printf("%s dostal bidu!", hraci[3].jmeno_hrace);
                delay(2000);
                gotoxy(10, 10);
                printf("                           ");
                break;
           
            }
           /* else if (baf[w] == 'x') {
                gotoxy(10, 10);
                printf("Vedle!");
                delay(3000);
                gotoxy(10, 10);
                printf("             ");
                
                break;
            }*/
            else {
                barva(0); 
                gotoxy(strela->x, strela->y);
                putc('*', stdout);
            }
            delay(200); //w++;
            }
            if (hraci[1].zasahy == 3) {
                vykresli_tank_mrtvej(1, 3);
            }
            if (hraci[2].zasahy == 3) {
                vykresli_tank_mrtvej(2, 3);
            }
            if (hraci[3].zasahy == 3) {
                vykresli_tank_mrtvej(3, 3);
        }
        /*while (strela->y != START_Y2) {
            strela->x = strela->x + (cos(alfa) * v0 * t) / 1;
            strela->y = strela->y - ((sin(alfa) * v0* t)+((1/2)*(-0,1)*t)) / 1;
            gotoxy(strela->x, strela->y);
            putc('*', stdout);
            t++; delay(1000);}*/
    // }    
    }
}
 
