//prova "blackbox"

#include <stdio.h>
#include <stdlib.h>

#define LATO 8

struct s_vec2d {
	int x;
	int y;
};
typedef struct s_vec2d vec2d;

struct s_elettrone {
	vec2d pos;
	vec2d dir;
	int uscito;
};
typedef struct s_elettrone elettrone;

struct s_atomo {
	vec2d pos;
};
typedef struct s_atomo atomo;

int posVettore(int x, int y, int largh);
void azzeraMat(int* campo, int lungh, int largh);
void stampaMat(int* , int , int , elettrone, atomo*, int);
void simulaElettrone(elettrone * e, atomo * vecAtomi, int qta);

int main(){
	int campo[LATO * LATO];
	
	azzeraMat(campo,LATO, LATO);
	
	elettrone elProva = {
		{0,3},	//pos
		{1,0},	//dir
		0
	};
	
	atomo arrAtomi[4];
	
	for(int iA = 0 ; iA<4; iA++) {
		arrAtomi[iA].pos.x = -1;
		arrAtomi[iA].pos.y = -1;
	}
	
	arrAtomi[0].pos.x = 5;
	arrAtomi[0].pos.y = 4;
	
	arrAtomi[1].pos.x = 5;
	arrAtomi[1].pos.y = 1;
	
	stampaMat(campo,LATO, LATO, elProva, arrAtomi, 4);
	
	for(int i=0;i<LATO;i++) {
		
		printf("Press Enter to step...\n");
		getchar();
		system("cls");
		simulaElettrone(&elProva, arrAtomi, 4);
		stampaMat(campo,LATO, LATO, elProva, arrAtomi, 4);
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

void stampaMat(int* campo, int lungh, int largh, elettrone elett, atomo* vecAtomi, int qtaAtomi){
	char valoreCampo;
	int x, y;
	int a = 0;
	for(y=0; y<lungh; y++){
		for(x=0; x<largh; x++){
			valoreCampo = campo[posVettore(x, y, largh)];
			
			if(elett.pos.x == x && elett.pos.y == y) 
				valoreCampo = 1;
				
			for(a = 0; a< qtaAtomi; a++) {
				if(vecAtomi[a].pos.x == x && vecAtomi[a].pos.y == y) 
					valoreCampo = 5;
			}
				
			printf("|%3d ", valoreCampo);
		}
		
		printf("\n");
		for(int lato=0; lato < largh; lato++)
			printf("+----");
		printf("\n");
	}
}

void simulaElettrone(elettrone * e, atomo* vecAtomi, int qtaAtomi) {
	
	int iAtomo;
	
	int altoDestra  = 0;
	int bassoDestra = 0;
	int altoSinistra  = 0;
	int bassoSinistra = 0;
	
	for(iAtomo = 0; iAtomo<qtaAtomi; iAtomo++) {
		atomo* a = &vecAtomi[iAtomo];
		
		if(altoDestra == 0 && (a->pos.x == e->pos.x + 1 && a->pos.y == e->pos.y - 1))
			altoDestra = 1;
		if(bassoDestra == 0 && (a->pos.x == e->pos.x + 1 && a->pos.y == e->pos.y + 1))
			bassoDestra = 1;
		
		if(altoSinistra == 0 && (a->pos.x == e->pos.x - 1 && a->pos.y == e->pos.y - 1))
			altoSinistra = 1;
		if(bassoSinistra == 0 && (a->pos.x == e->pos.x - 1 && a->pos.y == e->pos.y + 1))
			bassoSinistra = 1;
	}
	
	if(e->dir.x == 1 && e->dir.y == 0) {
		//verso destra
		
		if(altoDestra && bassoDestra) {
			e->dir.x = -1;
			e->dir.y = 0;
		} else if(altoDestra && !bassoDestra) {
			e->dir.x = 0;
			e->dir.y = 1;
		} else if(!altoDestra && bassoDestra) {
			e->dir.x = 0;
			e->dir.y = -1;
		}
	}
	
	if(e->dir.x == 0 && e->dir.y == -1) {
		//verso alto
		
		if(altoDestra && altoSinistra) {
			e->dir.x = 0;
			e->dir.y = -1;
		} else if(altoDestra && !altoSinistra) {
			e->dir.x = -1;
			e->dir.y = 0;
		} else if(!altoDestra && altoSinistra) {
			e->dir.x = 1;
			e->dir.y = 0;
		}
	}
	
	e->pos.x += e->dir.x;
	e->pos.y += e->dir.y;
}
