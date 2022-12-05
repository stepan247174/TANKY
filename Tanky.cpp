// Tanky.cpp : Defines the entry point for the application.
//

#include "Tanky.h"

using namespace std;

int main()
{
	SetConsoleTitle("Tanki pana Strika");

	int playersCount = hrac();

	OnAdd(playersCount);

	vymaz(); /* vymaze obraz */
	srand((unsigned int)time(NULL));
	RAM_ZED();
	//int key = MyGetch();
	VypisJmena(playersCount);
	sou_tan = alokuj_tank();

	for (int h = 1; h <= playersCount; h++) {
		vykresli_tank_start(h, 1);
	}
	int strelivo[300];
	                         
		do {
			for (int h = 1; h <= playersCount; h++) {
				int r = 1;
				barva(0);
				gotoxy(80 + r, 6);
				printf("Zadej rychlost strely: ");
				scanf("%d", &strelivo[r]);
				gotoxy(80 + r, 6);
				printf("                             ");
				if ((hraci[1].zasahy == 3) && (h == 1)) {
					h++;
				}
				if ((hraci[2].zasahy == 3) && (h == 2)) {
					h++;
				}
				if ((hraci[3].zasahy == 3) && (h == 3)) {
					h = h - 2;
				}
				else if ((hraci[1].zasahy == 3) && (h == 1)) {
					return 0;
				}
				int Smer = JakyTank(h);
				strelba(startyX[h], startyY[h], Smer, strelivo[r]);
				VypisJmena(playersCount);
				r++;
			}
		} while ((hraci[1].zasahy != 3) || (hraci[2].zasahy != 3) || (hraci[3].zasahy != 3));
	
	gotoxy(5, 5);
	return 0;
}
