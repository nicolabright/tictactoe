#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

#define PLAYER_O	1
#define PLAYER_X	2


struct MapSituation {
	int mappaValue[9];
	int score;
	struct MapSituation *actionsToMap[9];
};


void CopyMapStituation(struct MapSituation *mappaFrom, struct MapSituation *mappaTo) {
	for (int iPos=1; iPos<=9; iPos++) {
		(*mappaTo).mappaValue[iPos] = (*mappaFrom).mappaValue[iPos];
		(*mappaTo).actionsToMap[iPos] = (*mappaFrom).actionsToMap[iPos];
	}
	(*mappaTo).score = (*mappaFrom).score;
}

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

int evaluateTerna(struct MapSituation *mappa, int cella1, int cella2, int cella3, int player) {
	int valoreTernaOut = 0;
	int contatori[3];
	contatori[0]=0;	// 0 = spazio vuoto
	contatori[1]=0;	// 1 = player O
	contatori[2]=0;	// 2 = player X
	contatori[(*mappa).mappaValue[cella1]]++;
	contatori[(*mappa).mappaValue[cella2]]++;
	contatori[(*mappa).mappaValue[cella3]]++;
	if (player == PLAYER_O) {
		valoreTernaOut = contatori[0]*1 + contatori[1]*10 - contatori[2]*15;
	} else {
		valoreTernaOut = contatori[0]*1 - contatori[1]*15 - contatori[2]*10;
	}
	return valoreTernaOut;
}

int evaluateMap(struct MapSituation *mappa, int player) {
	int valoreMappa = 0;
	// Valuta il rischio di mosse CONTRO il player attuale (valuta la miglior DIFESA)
	// controllo Righe
	valoreMappa += evaluateTerna(mappa, 7, 8, 9, player);
	valoreMappa += evaluateTerna(mappa, 4, 5, 6, player);
	valoreMappa += evaluateTerna(mappa, 1, 2, 3, player);
	valoreMappa += evaluateTerna(mappa, 7, 4, 1, player);
	valoreMappa += evaluateTerna(mappa, 8, 5, 2, player);
	valoreMappa += evaluateTerna(mappa, 9, 6, 3, player);
	valoreMappa += evaluateTerna(mappa, 1, 5, 9, player);
	valoreMappa += evaluateTerna(mappa, 7, 5, 3, player);
	return (valoreMappa);
}

int getEvaluation(struct MapSituation *mappa, int testMove, int player) {
	struct MapSituation testMap;
	CopyMapStituation(mappa, &testMap);
	int valureBefore = evaluateMap(&testMap, player);
	if (player == PLAYER_O) {
		setActionPlayerO(&testMap, testMove);
	} else {
		setActionPlayerX(&testMap, testMove);
	}
	int valureAfter = evaluateMap(&testMap, player);
	// Evaluation
	return (valureAfter-valureBefore);
}

int getNextBestMove(struct MapSituation *mappa, int player) {
	int bestValue = -999;
	int bestMove = 0;
	// Array di scelte
	int bestMovesArray[9];
	int count_bestMovesArray=0;
	for (int iTestMove=1; iTestMove<=9; iTestMove++) {
		if (!isCellUsed(mappa, iTestMove)) {
			int newValue = getEvaluation(mappa, iTestMove, player);
			printf("   Caso mossa in %d => V=%d\n", iTestMove, newValue);
			if (bestValue < newValue) {
				bestValue = newValue;
				// Ricomincia una serie ancora migliore di mosse
				count_bestMovesArray = 1;
				bestMovesArray[count_bestMovesArray] = iTestMove;
			} else if (bestValue == newValue) {
				// Aggiunge altre mosse di egual qualità
				count_bestMovesArray++;
				bestMovesArray[count_bestMovesArray] = iTestMove;
			}
		}
	}
	// Quindi elenca le mosse (per debug)
	printf("Mosse possibili:\n");
	for(int iList=1; iList<=count_bestMovesArray; iList++) {
		printf("%d ", bestMovesArray[iList]);
	}
	printf("\n");
	// Quindi ne sceglie una a caso fra le migliori di egual merito
	bestMove = bestMovesArray[ (rand() % count_bestMovesArray) + 1 ];
	printf("Valore schema: O => %d | X => %d\n", evaluateMap(mappa, PLAYER_O), evaluateMap(mappa, PLAYER_X));
	printf("===> PLAYER=%d @ posiz=%d\n", player, bestMove);
	return (bestMove);
}

void main() {
	struct MapSituation map;

	srand(time(0));	// Randomize

	ClearMap(&map);
	PrintGrid(&map);
	int iIter = 0;
	int nextPos = 0;
	while( countCellsFree(&map) > 0 ) {
		if ( (++iIter % 2) == 0) {
			nextPos = getNextBestMove(&map, PLAYER_O);
			setActionPlayerO(&map, nextPos);
		} else {
			nextPos = getNextBestMove(&map, PLAYER_X);
			setActionPlayerX(&map, nextPos);
		}
		PrintGrid(&map);
	}

}
