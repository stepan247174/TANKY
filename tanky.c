// Tanky.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Tanky.h"

using namespace std;
int hraci() {
	char playersCount;
	printf("Zvolte pocet hracu: ");
	scanf("%c", &playersCount);
	
	switch(playersCount)
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

int main()
{
	int playersCount = hraci();

	if (playersCount >= 0)
	{
		printf("vsechno dobry");
	}
	else
	{
		printf("napicu");
	}

	return 0;
}
