#include <stdio.h>
#include <stdlib.h>
#include "vec2d.h"
//https://www.raylib.com/index.html

#define LATO 8
#define NUM_ATOMI 5

struct s_elettrone {
	vec2d pos;
	vec2d dir;
	int stato;
};
typedef struct s_elettrone elettrone;

struct s_atomo {
	vec2d pos;
};
typedef struct s_atomo atomo;

enum statoElettrone {
	CORRENTE,			//continua a viaggiare...
	ASSORBITO,			//qualcosa lo ha assorbito
	ASSORBITO_BORDO,	//assorbito al bordo
	USCITO				//uscito dalla griglia!
};

int posVettore(int x, int y, int largh);
void azzeraElettrone(elettrone * e);
void posizionaAtomi(atomo * arrAtomi, int qta);
void azzeraMat(int* campo, int lungh, int largh);
void stampaMat(int* , int , int , elettrone, atomo*, int);
int simulaElettrone(elettrone * e, atomo * vecAtomi, int qta, int lunghGriglia);
int scegliCella(int lungh);
void stampaStato(elettrone e);
void preparaLancio(elettrone * e, int lunghLato);
int controllaAssorbitoBordo(elettrone * e, atomo* a, int lunghGriglia);
void disegnaCella(int* campo, int x, int y,  int largh, elettrone elett, atomo* vecAtomi, int qtaAtomi);

vec2d dirDestra 	= {1, 0};
vec2d dirSinistra 	= {-1, 0};
vec2d dirAlto 		= {0, -1};
vec2d dirBasso 		= {0, 1};

int main(){
	int campo[LATO * LATO];
	azzeraMat(campo,LATO, LATO);
	
	elettrone elProva;
	azzeraElettrone(&elProva);
	
	atomo arrAtomi[NUM_ATOMI];
	posizionaAtomi(arrAtomi, NUM_ATOMI);
	
	stampaMat(campo,LATO, LATO, elProva, arrAtomi, NUM_ATOMI);
	
	preparaLancio(&elProva, LATO);
	
	getchar();
	system("cls");
	
	stampaMat(campo,LATO, LATO, elProva, arrAtomi, NUM_ATOMI);
	
	while(elProva.stato == CORRENTE) {
		printf("Press Enter to step...\n");
		getchar();
		system("cls");
		elProva.stato = simulaElettrone(&elProva, arrAtomi, NUM_ATOMI, LATO);
		stampaMat(campo,LATO, LATO, elProva, arrAtomi, NUM_ATOMI);
	}
	
	stampaStato(elProva);
}

void azzeraElettrone(elettrone * e){
	e->pos.x = 0;
	e->pos.y = 0;
	e->dir.x = 0;
	e->dir.y = 0;
	e->stato = CORRENTE;
}

void posizionaAtomi(atomo * arrAtomi, int qta) {
	for(int iA = 0 ; iA<qta; iA++) {
		arrAtomi[iA].pos.x = -1;
		arrAtomi[iA].pos.y = -1;
	}
	
	//todo: farli random
	arrAtomi[0].pos.x = 5;
	arrAtomi[0].pos.y = 4;
	
	arrAtomi[1].pos.x = 5;
	arrAtomi[1].pos.y = 1;
	
	arrAtomi[2].pos.x = 2;
	arrAtomi[2].pos.y = 1;
	
	arrAtomi[3].pos.x = 2;
	arrAtomi[3].pos.y = 7;
	
	arrAtomi[4].pos.x = 7;
	arrAtomi[4].pos.y = 6;
	
	
}

void stampaStato(elettrone e) {
	switch(e.stato) {
		case USCITO:
			printf("L'elettrone e' uscito dalla black box!\n");
			printf("Posizione finale: \n");
			infoVec(e.pos);
			break;
			
		case ASSORBITO:
			printf("L'elettrone e' stato assorbito!");
			break;
			
		case ASSORBITO_BORDO:
			printf("L'elettrone e' stato assorbito al bordo... !");
			break;
			
		default:
			printf("Non si sa che fine ha fatto...");
	}
}


int scegliCella(int lungh) {
	int cella = -1;
	
	printf("Da quale cella vuoi partire? \n");
	do {
		scanf("%d", &cella);
	} while(cella < 0 || cella >= lungh);
	return cella;
}

void preparaLancio(elettrone * e, int lunghLato) {
	char dirPartenza = '-';
	
	do {
		printf("Da quale direzione? (N S E O) : ");
		dirPartenza = getchar();
		//getchar();	//prende l'invio
		//printf("\nil valore e' %c (%d)\n", dirPartenza, dirPartenza);
	} while(dirPartenza != 'N' && dirPartenza != 'S' && dirPartenza != 'E' && dirPartenza != 'O');
	
	if(dirPartenza == 'N') {
		e->pos.y = 0;
		e->dir = dirBasso;
		e->pos.x = scegliCella(LATO);
	}
	
	if(dirPartenza == 'S') {
		e->pos.y = lunghLato - 1;
		e->dir = dirAlto;
		e->pos.x = scegliCella(LATO);
	}
	
	if(dirPartenza == 'O') {
		e->pos.x = 0;
		e->dir = dirDestra;
		e->pos.y = scegliCella(LATO);
	}
	
	if(dirPartenza == 'E') {
		e->pos.x = lunghLato - 1;
		e->dir = dirSinistra;
		e->pos.y = scegliCella(LATO);
	}
}

int posVettore(int x, int y, int largh) {
	return y*largh + x;
}

void azzeraMat(int* campo, int lungh, int largh){
	for(int y=0; y<largh; y++){
		for(int x=0; x<lungh; x++){
			campo[posVettore(x, y, largh)] = 0;
		}
	}
}

void disegnaCella(int* campo, int x, int y,  int largh, elettrone elett, atomo* vecAtomi, int qtaAtomi) {
	int a = 0;
	char valoreCampo = ' '; 	//campo[posVettore(x, y, largh)]; // al momento inutile
	
	if(elett.pos.x == x && elett.pos.y == y) 
		valoreCampo = 'e';
		
	for(a = 0; a< qtaAtomi; a++) {
		if(vecAtomi[a].pos.x == x && vecAtomi[a].pos.y == y) 
			valoreCampo = 'a';
	}
	
	printf("|%3c ", valoreCampo);
}

void stampaMat(int* campo, int lungh, int largh, elettrone elett, atomo* vecAtomi, int qtaAtomi){
	int x, y;
	for(y=-1; y<lungh+1; y++){
		
		for(x=-1; x<largh+1; x++){
				
				//griglia esterna
				if(y == -1 && x == -1) {
					printf("%3c", ' ');
				} else if (y >= 0 && x == -1) {
					//NORD
					printf("%5d", y);
				} else if (y == -1 && x >= 0) {
					//OVEST
					printf("%5d", x);
				} else if (y >= 0 && x == lungh) {
					//EST
					printf("%5d", y);
				} else if (y == largh && x >= 0) {
					//SUD
					printf("%5d", x);
				}
				
				if(y < 0 || x < 0 || x >= lungh || y >= largh)
					continue;
				
				//griglia effettiva
				disegnaCella(campo, x, y, largh, elett, vecAtomi, qtaAtomi);
		}
		
		printf("\n");
		
		for(int lato=-1; y < largh && lato < largh; lato++){
			//griglia esterna
			if(lato == -1) {
				printf("%5c", ' ');
				continue;
			}
			
			//griglia effettiva
			printf("+----");
		}
		printf("\n");
	}
}

int controllaAssorbitoBordo(elettrone * e, atomo* a, int lunghGriglia) {
	int assorbitoBordo = 0;
	
	//assorbito bordo (SUD)
	if(e->pos.y == lunghGriglia-1 && (a->pos.x == e->pos.x+1 && a->pos.y == e->pos.y))
		assorbitoBordo = 1;
		
	if(e->pos.y == lunghGriglia-1 && (a->pos.x == e->pos.x-1 && a->pos.y == e->pos.y))
		assorbitoBordo = 1;
	
	//assorbito bordo (NORD)
	if(e->pos.y == 0 && (a->pos.x == e->pos.x+1 && a->pos.y == e->pos.y))
		assorbitoBordo = 1;
		
	if(e->pos.y == 0 && (a->pos.x == e->pos.x-1 && a->pos.y == e->pos.y))
		assorbitoBordo = 1;
		
	//assorbito bordo (OVEST)
	if(e->pos.x == 0 && (a->pos.y == e->pos.y+1 && a->pos.x == e->pos.x))
		assorbitoBordo = 1;
		
	if(e->pos.x == 0 && (a->pos.y == e->pos.y-1 && a->pos.x == e->pos.x))
		assorbitoBordo = 1;
		
	//assorbito bordo (EST)
	if(e->pos.x == lunghGriglia-1 && (a->pos.y == e->pos.y+1 && a->pos.x == e->pos.x))
		assorbitoBordo = 1;
		
	if(e->pos.x == lunghGriglia-1 && (a->pos.y == e->pos.y-1 && a->pos.x == e->pos.x))
		assorbitoBordo = 1;
		
	return assorbitoBordo;
}

void aggiornaDirezioneElettrone(elettrone * e, int altoDestra, int bassoDestra,	int altoSinistra, int bassoSinistra) {
	if(confrontaVec(e->dir, dirAlto)) {
		if(altoDestra && altoSinistra) {
			e->dir = dirBasso;
		} else if(altoDestra && !altoSinistra) {
			e->dir = dirSinistra;
		} else if(!altoDestra && altoSinistra) {
			e->dir = dirDestra;
		}
	}
	
	if(confrontaVec(e->dir, dirBasso)) {
		if(bassoDestra && bassoSinistra) {
			e->dir = dirAlto;
		} else if(bassoDestra && !bassoSinistra) {
			e->dir = dirSinistra;
		} else if(!bassoDestra && bassoSinistra) {
			e->dir = dirDestra;
		}
	}
	
	if(confrontaVec(e->dir, dirDestra)) {
		if(altoDestra && bassoDestra) {
			e->dir = dirSinistra;
		} else if(altoDestra && !bassoDestra) {
			e->dir = dirBasso;
		} else if(!altoDestra && bassoDestra) {
			e->dir = dirAlto;
		}
	}
	
	if(confrontaVec(e->dir, dirSinistra)) {
		if(altoSinistra && bassoSinistra) {
			e->dir = dirDestra;
		} else if(altoSinistra && !bassoSinistra) {
			e->dir = dirBasso;
		} else if(!altoSinistra && bassoSinistra) {
			e->dir = dirAlto;
		}
	}
}

int simulaElettrone(elettrone * e, atomo* vecAtomi, int qtaAtomi, int lunghGriglia) {
	
	int iAtomo;
	int assorbito = 0;
	int assorbitoBordo = 0;
	int altoDestra  = 0;
	int bassoDestra = 0;
	int altoSinistra  = 0;
	int bassoSinistra = 0;
	
	int statoFinale = CORRENTE;
	
	for(iAtomo = 0; iAtomo<qtaAtomi; iAtomo++) {
		atomo* a = &vecAtomi[iAtomo];
		
		if(assorbito == 0 && (a->pos.x == e->pos.x && a->pos.y == e->pos.y)){
			assorbito = 1;
			break;
		}
		
		if(assorbitoBordo == 0) {
			assorbitoBordo = controllaAssorbitoBordo(e, a, lunghGriglia);
		}
		
		if(altoDestra == 0 && (a->pos.x == e->pos.x + 1 && a->pos.y == e->pos.y - 1))
			altoDestra = 1;
		if(bassoDestra == 0 && (a->pos.x == e->pos.x + 1 && a->pos.y == e->pos.y + 1))
			bassoDestra = 1;
		
		if(altoSinistra == 0 && (a->pos.x == e->pos.x - 1 && a->pos.y == e->pos.y - 1))
			altoSinistra = 1;
		if(bassoSinistra == 0 && (a->pos.x == e->pos.x - 1 && a->pos.y == e->pos.y + 1))
			bassoSinistra = 1;
	}
	
	if(assorbito){
		statoFinale = ASSORBITO;
		return statoFinale;
	}
	
	if(assorbitoBordo) {
		statoFinale = ASSORBITO_BORDO;
		return statoFinale;
	}
	
	aggiornaDirezioneElettrone(e, altoDestra, bassoDestra, altoSinistra, bassoSinistra);
	
	e->pos.x += e->dir.x;
	e->pos.y += e->dir.y;
	
	if(e->pos.x >= lunghGriglia || e->pos.y >= lunghGriglia || e->pos.x < 0 || e->pos.y < 0) {
		statoFinale = USCITO;
	}
	
	return statoFinale;
}
