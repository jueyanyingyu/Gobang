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

#define Large 1000000000
#define Small -1000000000

#define LianWu 500000000
#define HuoSi 100000000
#define ChongSi 20000000
#define HuoSan 4000000
#define MianSan 800000
#define HuoEr 700000
#define MianEr 100000
#define DanYi 1000
#define Normal 10

#define FLOOR 6 


#define COUNT 100000

typedef struct {
	int x0;
	int y0;
	int score;
}coordinate;
typedef struct {
	int broad[N][N];
}broad;
typedef struct {
	int scan3x;
	int scan3y;
	int scan4x;
	int scan4y;
}size;

void putbroad(broad abroad);
int winjudge(broad abroad,coordinate todo,int WorB);
int down(coordinate todo,int WorB);
//void cheki();
//void cpybroad();
//int isDraw();
coordinate ai(int WorB);
//int shapejudge(int,int);
int metajudge(broad abroad,coordinate todo,int dx,int dy,int WorB);
int pointjudge(int x0,int y0,broad tpbd);
int metacount(int dx,int dy,int x0,int y0,broad tpbd);
int scanning(int level,size newsize,int PorC,int WorB,broad tpbd);
size expand(size tpsize,int x0,int y0);
void sort(int PorC,broad tpbd,coordinate* cdlist,int length);
int kill(int level,size newsize,int PorC,int WorB,broad tpbd);
//int MonteCarlo(int level,int scan3x,int scan3y,int scan4x,int scan4y,int PorC);
//int zobrist(point list,int level);
//int searchhash(int hash);
