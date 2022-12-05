// Tanky.cpp : Defines the entry point for the application.
//

#include "Tanky.h"

using namespace std;

int main()
{
	SetConsoleTitle("Tanki pana Strika");

	int playersCount = hraci();

	vymaz(); /* vymaze obraz */
	srand((unsigned int)time(NULL));
	RAM_ZED();
	//int key = MyGetch();
	sou_tan = alokuj_tank();

	for (int h = 1; h <= playersCount; h++) {
		vykresli_tank_start(h, 1);
	}

	//do {
		for (int h = 1; h <= playersCount; h++) {
			/*gotoxy(10, 10);
			printf("               ");
			gotoxy(5, 5);
			printf(" Kam strilis?");*/

			//char key = getchar();
			//int strana=0;

			//gotoxy(5, 5);
			//printf("                       ");

			/*if (key = 'p') {
				strana = 1;

			}
			else if (key = 'l') {
				strana = -1;
				}*/
			strelba(startyX[h], startyY[h]);
		}
	//} while (playersCount != 4);
	gotoxy(5, 5);
	return 0;
}
