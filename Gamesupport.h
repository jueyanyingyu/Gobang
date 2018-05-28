#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

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

#define LianWu 500000
#define HuoSi 120000
#define ChongSi 110000
#define HuoSan 100000
#define MianSan 10000
#define HuoEr 10000
#define MianEr 1000
#define DanYi 100
#define Normal 1000
#define FLOOR 4

#define COUNT 100000

typedef struct {			//单点数据结构体 
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
point scanning(int level,int scan3x,int scan3y,int scan4x,int scan4y,int PorC,int WorB,point list);
int MonteCarlo(int level,int scan3x,int scan3y,int scan4x,int scan4y,int PorC);
int zobrist(point list,int level);
int searchhash(int hash);
