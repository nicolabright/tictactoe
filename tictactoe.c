#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

#define FREE_CELL	0
#define PLAYER_O	1
#define PLAYER_X	2

#define STATUS_NORMAL_GAME	0
#define STATUS_LOSE			1
#define STATUS_TIE			2
#define STATUS_WIN			3

typedef int bool;
#define true 1
#define false 0

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
	printf("       |       |       \n");
	printf("   %c   |   %c   |   %c   \n", simboli[7], simboli[8], simboli[9]);
	printf("       |       |       \n");
	printf("-------+-------+-------\n");
	printf("       |       |       \n");
	printf("   %c   |   %c   |   %c   \n", simboli[4], simboli[5], simboli[6]);
	printf("       |       |       \n");
	printf("-------+-------+-------\n");
	printf("       |       |       \n");
	printf("   %c   |   %c   |   %c   \n", simboli[1], simboli[2], simboli[3]);
	printf("       |       |       \n");
}

void PrintWeights(int weights[10]) {
	char str_weight_1[20];
	char str_weight_2[20];
	char str_weight_3[20];
	char str_weight_4[20];
	char str_weight_5[20];
	char str_weight_6[20];
	char str_weight_7[20];
	char str_weight_8[20];
	char str_weight_9[20];
	if (weights[1]!=-999) {
		sprintf(str_weight_1, "%d\0", weights[1]);
	} else {
		strcpy(str_weight_1, " \0");
	}
	if (weights[2]!=-999) {
		sprintf(str_weight_2, "%4d\0", weights[2]);
	} else {
		strcpy(str_weight_2, " \0");
	}
	if (weights[3]!=-999) {
		sprintf(str_weight_3, "%4d\0", weights[3]);
	} else {
		strcpy(str_weight_3, " \0");
	}
	if (weights[4]!=-999) {
		sprintf(str_weight_4, "%4d\0", weights[4]);
	} else {
		strcpy(str_weight_4, " \0");
	}
	if (weights[5]!=-999) {
		sprintf(str_weight_5, "%4d\0", weights[5]);
	} else {
		strcpy(str_weight_5, " \0");
	}
	if (weights[6]!=-999) {
		sprintf(str_weight_6, "%4d\0", weights[6]);
	} else {
		strcpy(str_weight_6, " \0");
	}
	if (weights[7]!=-999) {
		sprintf(str_weight_7, "%4d\0", weights[7]);
	} else {
		strcpy(str_weight_7, " \0");
	}
	if (weights[8]!=-999) {
		sprintf(str_weight_8, "%4d\0", weights[8]);
	} else {
		strcpy(str_weight_8, " \0");
	}
	if (weights[9]!=-999) {
		sprintf(str_weight_9, "%4d\0", weights[9]);
	} else {
		strcpy(str_weight_9, " \0");
	}
	printf("\n");
	printf("Valore mosse: \t\t       |       |       \n");
	printf("\t\t\t %4s  | %4s  | %4s  \n", str_weight_7, str_weight_8, str_weight_9);
	printf("\t\t\t       |       |       \n");
	printf("\t\t\t-------+-------+-------\n");
	printf("\t\t\t       |       |       \n");
	printf("\t\t\t %4s  | %4s  | %4s  \n", str_weight_4, str_weight_5, str_weight_6);
	printf("\t\t\t       |       |       \n");
	printf("\t\t\t-------+-------+-------\n");
	printf("\t\t\t       |       |       \n");
	printf("\t\t\t %4s  | %4s  | %4s  \n", str_weight_1, str_weight_2, str_weight_3);
	printf("\t\t\t       |       |       \n");
}

void PrintGridAndWeights(struct MapSituation *mappa, int weights[10]) {
	//____________________012
	char *listaSimboli = " OX\n";
	char simboli[10];
	for(int iPos=1; iPos<=9; iPos++) {
		simboli[iPos] = listaSimboli[(*mappa).mappaValue[iPos]];
	}
	// // // // // // // //
	char str_weight_1[20];
	char str_weight_2[20];
	char str_weight_3[20];
	char str_weight_4[20];
	char str_weight_5[20];
	char str_weight_6[20];
	char str_weight_7[20];
	char str_weight_8[20];
	char str_weight_9[20];
	if (weights[1]!=-999) {
		sprintf(str_weight_1, "%d\0", weights[1]);
	} else {
		strcpy(str_weight_1, " \0");
	}
	if (weights[2]!=-999) {
		sprintf(str_weight_2, "%4d\0", weights[2]);
	} else {
		strcpy(str_weight_2, " \0");
	}
	if (weights[3]!=-999) {
		sprintf(str_weight_3, "%4d\0", weights[3]);
	} else {
		strcpy(str_weight_3, " \0");
	}
	if (weights[4]!=-999) {
		sprintf(str_weight_4, "%4d\0", weights[4]);
	} else {
		strcpy(str_weight_4, " \0");
	}
	if (weights[5]!=-999) {
		sprintf(str_weight_5, "%4d\0", weights[5]);
	} else {
		strcpy(str_weight_5, " \0");
	}
	if (weights[6]!=-999) {
		sprintf(str_weight_6, "%4d\0", weights[6]);
	} else {
		strcpy(str_weight_6, " \0");
	}
	if (weights[7]!=-999) {
		sprintf(str_weight_7, "%4d\0", weights[7]);
	} else {
		strcpy(str_weight_7, " \0");
	}
	if (weights[8]!=-999) {
		sprintf(str_weight_8, "%4d\0", weights[8]);
	} else {
		strcpy(str_weight_8, " \0");
	}
	if (weights[9]!=-999) {
		sprintf(str_weight_9, "%4d\0", weights[9]);
	} else {
		strcpy(str_weight_9, " \0");
	}
	printf("\n");
	printf("       |       |       \t\t       |       |       \n");
	printf("   %c   |   %c   |   %c   \t\t %4s  | %4s  | %4s  \n", simboli[7], simboli[8], simboli[9], str_weight_7, str_weight_8, str_weight_9);
	printf("       |       |       \t\t       |       |       \n");
	printf("-------+-------+-------\t\t-------+-------+-------\n");
	printf("       |       |       \t\t       |       |       \n");
	printf("   %c   |   %c   |   %c   \t\t %4s  | %4s  | %4s  \n", simboli[4], simboli[5], simboli[6], str_weight_4, str_weight_5, str_weight_6);
	printf("       |       |       \t\t       |       |       \n");
	printf("-------+-------+-------\t\t-------+-------+-------\n");
	printf("       |       |       \t\t       |       |       \n");
	printf("   %c   |   %c   |   %c   \t\t %4s  | %4s  | %4s  \n", simboli[1], simboli[2], simboli[3], str_weight_1, str_weight_2, str_weight_3);
	printf("       |       |       \t\t       |       |       \n");
	printf("\n");
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
	int ref_Me = 0;
	int ref_Enemy = 0;
	int ref_Free = FREE_CELL;
	contatori[0]=0;	// 0 = spazio vuoto
	contatori[1]=0;	// 1 = player O
	contatori[2]=0;	// 2 = player X
	contatori[(*mappa).mappaValue[cella1]]++;
	contatori[(*mappa).mappaValue[cella2]]++;
	contatori[(*mappa).mappaValue[cella3]]++;
	if (player == PLAYER_O) {
		ref_Me = PLAYER_O;
		ref_Enemy = PLAYER_X;
	} else {
		ref_Me = PLAYER_X;
		ref_Enemy = PLAYER_O;
	}
	if (contatori[ref_Me]==1 && contatori[ref_Free]==2) valoreTernaOut += 50;
	if (contatori[ref_Me]==2 && contatori[ref_Free]==1) valoreTernaOut += 100;
	if (contatori[ref_Me]==2 && contatori[ref_Enemy]==1) valoreTernaOut += 150;
	if (contatori[ref_Me]==3 && contatori[ref_Free]==0) valoreTernaOut += 300;
	if (contatori[ref_Me]==1 && contatori[ref_Enemy]==2) valoreTernaOut += 350;
	return valoreTernaOut;
}

int evaluateMap(struct MapSituation *mappa, int player) {
	int valoreMappa = 0;
	// Valuta sia in ATTACCO che in DIFESA, per ogni linea possibile
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
	int forceCorrection = 0;
	if (testMove==5) {
		// Giocare la cella centrale porta svantaggio (ad una parità certa...)
		forceCorrection = -50;
	}
	// Evaluation
	return (valureAfter - valureBefore  + forceCorrection);
}

int getNextBestMove(struct MapSituation *mappa, int player) {
	int bestValue = -999;
	int bestMove = 0;
	// Array di scelte
	int bestMovesArray[9];
	int weightsOfMove[10];
	for (int irs=1; irs<=9; irs++) {
		weightsOfMove[irs] = -999;
	}
	int count_bestMovesArray=0;
	for (int iTestMove=1; iTestMove<=9; iTestMove++) {
		if (!isCellUsed(mappa, iTestMove)) {
			int newValue = getEvaluation(mappa, iTestMove, player);
			weightsOfMove[iTestMove] = newValue;
//			printf("   Caso mossa in %d => V=%d\n", iTestMove, newValue);
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
	// // PrintWeights(weightsOfMove);
	PrintGridAndWeights(mappa, weightsOfMove);
//	for(int iList=1; iList<=count_bestMovesArray; iList++) {
//		printf("%d ", bestMovesArray[iList]);
//	}
//	printf("\n");
	// Quindi ne sceglie una a caso fra le migliori di egual merito
	bestMove = bestMovesArray[(rand() % count_bestMovesArray) + 1];
	if (player==PLAYER_O) {
		printf("Valore mossa scelta PLAYER O su [%d]=> %d\n", bestMove, bestValue);
	} else {
		printf("Valore mosse scelta PLAYER X su [%d]=> %d\n", bestMove, bestValue);
	}
	return (bestMove);
}

int GetGameStatus(struct MapSituation *mappa, int player) {
	int m[10];
	int mP = player;
	for(int iMap=1; iMap<=9; iMap++) {
		m[iMap] = (*mappa).mappaValue[iMap];
	}
	if ( (m[1]==mP) && (m[2]==mP) && (m[3]==mP) ) return (STATUS_WIN);
	if ( (m[4]==mP) && (m[5]==mP) && (m[6]==mP) ) return (STATUS_WIN);
	if ( (m[7]==mP) && (m[8]==mP) && (m[9]==mP) ) return (STATUS_WIN);
	if ( (m[1]==mP) && (m[4]==mP) && (m[7]==mP) ) return (STATUS_WIN);
	if ( (m[2]==mP) && (m[5]==mP) && (m[8]==mP) ) return (STATUS_WIN);
	if ( (m[3]==mP) && (m[6]==mP) && (m[9]==mP) ) return (STATUS_WIN);
	if ( (m[1]==mP) && (m[5]==mP) && (m[9]==mP) ) return (STATUS_WIN);
	if ( (m[3]==mP) && (m[5]==mP) && (m[7]==mP) ) return (STATUS_WIN);
	return(STATUS_NORMAL_GAME);
}


void main() {
	struct MapSituation map;

	srand(time(0));	// Randomize

	ClearMap(&map);
	//PrintGrid(&map);
	int iIter = 0;
	int nextPos = 0;
	bool bGameRunning = true;
	while( (countCellsFree(&map)>0) && (bGameRunning==true) ) {
		if ( (++iIter % 2) == 0) {
			nextPos = getNextBestMove(&map, PLAYER_O);
			setActionPlayerO(&map, nextPos);
		} else {
			nextPos = getNextBestMove(&map, PLAYER_X);
			setActionPlayerX(&map, nextPos);
		}
		if (GetGameStatus(&map, PLAYER_O) == STATUS_WIN) {
			printf("Player 'O' wins!\n");
			bGameRunning = false;
		}
		if (GetGameStatus(&map, PLAYER_X) == STATUS_WIN) {
			printf("Player 'X' wins!\n");
			bGameRunning = false;
		}
		//PrintGrid(&map);
	}
	if (iIter>=9) {
		printf("Game TIE\n");
	}
	PrintGrid(&map);

}
