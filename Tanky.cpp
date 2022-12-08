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
				
				int Smer = JakyTank(h);
				strelba(startyX[h], startyY[h], Smer, strelivo[r]);
				VypisJmena(playersCount);
				if ((hraci[1].zasahy == 3)) {
					h++;
					gotoxy(10, 10); barva(3);
					printf("%s prohral", hraci[1].jmeno_hrace);
					gotoxy(10, 11); barva(1);
					printf("%s vyhrava!!!!!!!!!!!!!!", hraci[2].jmeno_hrace); delay(10000);
					gotoxy(10, 5); barva(0); exit(0);
				}
				if ((hraci[2].zasahy == 3)) {
					h++;
					gotoxy(10, 11); barva(3);
					printf("%s prohral", hraci[2].jmeno_hrace);
					gotoxy(10, 10); barva(1);
					printf("%s vyhrava!!!!!!!!!!!!!!!!!!", hraci[1].jmeno_hrace); delay(5000);
					gotoxy(10, 5); barva(0); exit(0);
				}
				if ((hraci[3].zasahy == 3)) {
					h = h++;
					gotoxy(10, 10); barva(3);
					printf("%s prohral", hraci[3].jmeno_hrace);
					return 0;
					gotoxy(10, 11); barva(1);
					printf("%s prohral", hraci[3].jmeno_hrace); delay(2000);
					gotoxy(10, 5); barva(0); exit(0);
				}
				r++;
			}
		} while ((hraci[1].zasahy != 3) || (hraci[2].zasahy != 3) || (hraci[3].zasahy != 3));
	
	gotoxy(5, 5);
	return 0;
}
