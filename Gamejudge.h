#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 15
#define MAXSTEPS 225
#define DRAW 0
#define WHITE_WIN 1
#define BLACK_WIN 2
#define TRUE 1
#define FALSE 0
#define WHITE -1
#define BLACK 1
#define NONE 0

int n[N][N]={0};
int WorB=WHITE;
int x=-1,y=-1;
int lastx,lasty;
int steps=0;

void putbroad();
int winjudge(); 
int metajudge(int dx,int dy);
int down();
void cheki();

