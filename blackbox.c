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
void stampaMat(int* , int , int , elettrone, atomo);
void simulaElettrone(elettrone * e, atomo * a);

int main(){
	int campo[LATO * LATO];
	
	azzeraMat(campo,LATO, LATO);
	
	elettrone elProva = {
		{0,3},	//pos
		{1,0},	//dir
		0
	};
	
	atomo at = {
		{5,4} // pos
	};
	
	stampaMat(campo,LATO, LATO, elProva, at);
	
	for(int i=0;i<LATO;i++) {
		
		printf("Press Enter to step...\n");
		getchar();
		system("cls");
		simulaElettrone(&elProva, &at);
		stampaMat(campo,LATO, LATO, elProva, at);
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

void stampaMat(int* campo, int lungh, int largh, elettrone elett, atomo at){
	char valoreCampo;
	int x, y;
	
	for(y=0; y<lungh; y++){
		for(x=0; x<largh; x++){
			valoreCampo = campo[posVettore(x, y, largh)];
			
			if(elett.pos.x == x && elett.pos.y == y) 
				valoreCampo = 1;
				
			if(at.pos.x == x && at.pos.y == y) 
				valoreCampo = 5;
				
			printf("|%3d ", valoreCampo);
		}
		
		printf("\n");
		for(int lato=0; lato < largh; lato++)
			printf("+----");
		printf("\n");
	}
}

void simulaElettrone(elettrone * e, atomo * a) {
	if(e->dir.x == 1 && e->dir.y == 0) {
		//verso destra
		int altoDestra  = a->pos.x == e->pos.x + 1 && a->pos.y == e->pos.y - 1;
		int bassoDestra = a->pos.x == e->pos.x + 1 && a->pos.y == e->pos.y + 1;
		
		if(altoDestra && bassoDestra) {	//due atomi diversi
			e->dir.x = -1;
			e->dir.y = 0;
		} else if(altoDestra) {
			e->dir.x = 0;
			e->dir.y = 1;
		} else if(bassoDestra) {
			e->dir.x = 0;
			e->dir.y = -1;
		}
	}
	
	e->pos.x += e->dir.x;
	e->pos.y += e->dir.y;
}
