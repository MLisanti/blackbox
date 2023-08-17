#include <stdio.h>
#include <math.h>

struct vec2d_s {
	int x;
	int y;
};
typedef struct vec2d_s vec2d;

vec2d vec_dirDestra 	= {1, 0};
vec2d vec_dirSinistra 	= {-1, 0};
vec2d vec_dirAlto 		= {0, 1};
vec2d vec_dirBasso 		= {0, -1};

void azzeraVec(vec2d* a);
void infoVec(vec2d a);
vec2d sommaVec(vec2d a, vec2d b);
vec2d diffVec(vec2d a, vec2d b);
vec2d moltVec(vec2d a, vec2d b);
float magnitudineVec(vec2d a);
int confrontaVec(vec2d a, vec2d b);

//extern:
//https://www.geeksforgeeks.org/understanding-extern-keyword-in-c/

//portare in file con definizioni
void azzeraVec(vec2d* a) {
	a->x = 0;
	a->y = 0;
}

void infoVec(vec2d a) {
	printf("(%d, %d)\n", a.x, a.y);
}

vec2d sommaVec(vec2d a, vec2d b) {
	vec2d res;
	azzeraVec(&res);
	
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	
	return res;
}

vec2d diffVec(vec2d a, vec2d b) {
	vec2d res;
	azzeraVec(&res);
	
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	
	return res;
}

vec2d moltVec(vec2d a, vec2d b) {
	vec2d res;
	azzeraVec(&res);
	
	res.x = a.x * b.x;
	res.y = a.y * b.y;
	
	return res;
}

float magnitudineVec(vec2d a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

int confrontaVec(vec2d a, vec2d b) {
	return a.x == b.x && a.y == b.y;
}
