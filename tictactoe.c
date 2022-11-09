#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

struct MapSituation {
	int mappaValue[9];
	int score;
	struct MapSituation *actionsToMap[9];
};


void ClearMap(struct MapSituation *mappa) {
	(*mappa).mappaValue[1] = 0;
	(*mappa).mappaValue[2] = 0;
	(*mappa).mappaValue[3] = 0;
	(*mappa).mappaValue[4] = 0;
	(*mappa).mappaValue[5] = 0;
	(*mappa).mappaValue[6] = 0;
	(*mappa).mappaValue[7] = 0;
	(*mappa).mappaValue[8] = 0;
	(*mappa).mappaValue[9] = 0;
}

void PrintGrid(struct MapSituation *mappa) {
	//____________________012
	char *listaSimboli = " OX\n";
	char simboli[10];
	for(int iPos=1; iPos<=9; iPos++) {
		simboli[iPos] = listaSimboli[(*mappa).mappaValue[iPos]];
	}
	printf("\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c  \n", simboli[7], simboli[8], simboli[9]);
	printf("     |     |     \n");
	printf("-----+-----+-----\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c  \n", simboli[4], simboli[5], simboli[6]);
	printf("     |     |     \n");
	printf("-----+-----+-----\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c  \n", simboli[1], simboli[2], simboli[3]);
	printf("     |     |     \n");
}


void setActionPlayerClear(struct MapSituation *mappa, int cellaPos) {
	(*mappa).mappaValue[cellaPos] = 0;
}

void setActionPlayerO(struct MapSituation *mappa, int cellaPos) {
	(*mappa).mappaValue[cellaPos] = 1;
}

void setActionPlayerX(struct MapSituation *mappa, int cellaPos) {
	(*mappa).mappaValue[cellaPos] = 2;
}

bool isCellUsed(struct MapSituation *mappa, int cellaPos) {
	if ((*mappa).mappaValue[cellaPos] != 0) {
		return true;
	}
	return false;
}

int countCellsFree(struct MapSituation *mappa) {
	int countCellFree = 0;
	for (int iPos=1; iPos<=9; iPos++) {
		if ((*mappa).mappaValue[iPos] == 0) countCellFree++;
	}
	return (countCellFree);
}

void main() {
	struct MapSituation map;

	ClearMap(&map);
	srand( time(0) );
	PrintGrid(&map);
	int iIter = 0;
	while( countCellsFree(&map)>0 ) {
		int nextPos = 0;
		do {
			nextPos = (rand() % 9) + 1;
		} while (isCellUsed(&map, nextPos));
		if (++iIter % 2 == 0) {
			setActionPlayerO(&map, nextPos);
		} else {
			setActionPlayerX(&map, nextPos);
		}
		PrintGrid(&map);
	}

}
