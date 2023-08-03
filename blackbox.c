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

int posVettore(int x, int y, int largh);
void azzeraMat(int* campo, int lungh, int largh);
void stampaMat(int* , int , int , elettrone);
void simulaElettrone(elettrone * e);

int main(){
	int campo[LATO * LATO];
	
	azzeraMat(campo,LATO, LATO);
	
	elettrone elProva = {
		{0,0},	//pos
		{1,0},	//dir
		0
	};
	
	stampaMat(campo,LATO, LATO, elProva);
	
	for(int i=0;i<LATO;i++) {
		
		printf("Press Enter to step...\n");
		getchar();
		system("cls");
		simulaElettrone(&elProva);
		stampaMat(campo,LATO, LATO, elProva);
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

void stampaMat(int* campo, int lungh, int largh, elettrone elett){
	char valoreCampo;
	int x, y;
	
	for(y=0; y<lungh; y++){
		for(x=0; x<largh; x++){
			valoreCampo = campo[posVettore(x, y, largh)];
			
			if(elett.pos.x == x && elett.pos.y == y) 
				valoreCampo = 1;
				
			printf("|%3d ", valoreCampo);
		}
		
		printf("\n");
		for(int lato=0; lato < largh; lato++)
			printf("+----");
		printf("\n");
	}
}

void simulaElettrone(elettrone * e) {
	e->pos.x += + e->dir.x;
	e->pos.y += + e->dir.y;
}
