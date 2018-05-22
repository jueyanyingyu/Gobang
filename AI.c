#include "ShapeType.h"

int shapejudge(int tox,int toy) {
	metacount(1,0);
    metacount(1,1);
    metacount(0,1);
    metacount(-1,1);
}
int metacount(int dx,int dy) {
	int side=0,oside=0;
	int flag1,flag2;
    for(int i=1,flag1=1; (x+i*dx>=0&&x+i*dx<N&&y+i*dy>=0&&y+i*dy<N)&&(n[x+i*dx][y+i*dy]==WorB||(flag1>0&&n[x+i*dx][y+i*dy]==NONE,flag1--))&&i<5; i++) {
        side++;
    }
    for(int i=1,flag2=1; (x-i*dx>=0&&x-i*dx<N&&y-i*dy>=0&&y-i*dy<N)&&(n[x-i*dx][y-i*dy]==WorB||(flag2>0&&n[x+i*dx][y+i*dy]==NONE,flag2--))&&i<5; i++) {
        oside++;
    }
    if(side+oside==4) {
    	return LianWu;
    } else if (side+oside==3) {
    	
	}
}
