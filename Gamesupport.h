#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 15
#define MAXSTEPS 225
#define DRAW 0
#define TRUE 1
#define FALSE 0
#define WHITE -1
#define BLACK 1
#define NONE 0
#define COMPUTER 1
#define PLAYER -1

#define LianWu 100000000
#define HuoSi 10000000
#define ChongSi 1000000
#define HuoSan 100000
#define MianSan 1000
#define HuoEr 1000
#define MianEr 100
#define DanYi 10
#define Normal 100

#define FLOOR 5

typedef struct {
	int ifcut;
	int score;
	int todownx[FLOOR];
	int todowny[FLOOR];
}point;

void putbroad();
int winjudge();
int metajudge(int dx,int dy);
int down();
void cheki();
void cpybroad();
int isDraw();
void ai();
int shapejudge(int,int);
int metajudge(int dx,int dy);
int pointjudge(int x0,int y0,int PorC);
int metacount(int dx,int dy,int x0,int y0);
point scanning(int level,int,int,int,int,int,point);
