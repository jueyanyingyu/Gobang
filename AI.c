#include "Gamesupport.h"

extern int n[N][N];
extern int WorB;
extern int ComHd;
extern int PorC;
extern int x,y;
extern int lastx,lasty;
extern int steps;
extern int scan1x;
extern int scan1y;
extern int scan2x;
extern int scan2y;
extern int times;
extern int lastdownx[N*N];
extern int lastdowny[N*N];

int m[N][N];
int mscore[FLOOR];
point list,todo;

void cpybroad() {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            m[i][j]=n[i][j];
        }
    }
    return;
}
void ai() {
    if (0) {
		
    } else {
        cpybroad();
        for (int i=0; i<FLOOR; i++) {
            if (i%2==0) {
                mscore[i]=1000000000;
            } else {
                mscore[i]=-1000000000;
            }
        }
        list.ifcut=0;
        list.score=0;
        list.todownx[0]=0;
        list.todowny[0]=0;
        todo=scanning(0,scan1x,scan1y,scan2x,scan2y,COMPUTER,list);
        x=todo.todownx[0];
        y=todo.todowny[0];
        cpybroad();
    }
}
int pointjudge(int x0,int y0,int PorC) {
    if (m[x0][y0]==NONE) {
        return 0;
    } else {
        return PorC*(metacount(1,0,x0,y0)+metacount(1,1,x0,y0)+metacount(0,1,x0,y0)+metacount(-1,1,x0,y0));
    }
}
int metacount(int dx,int dy,int x0,int y0) {
    int color=m[x0][y0];
    int side=0,oside=0;
    int sides=0;
    int osides=0;
    int flag1=1;
    int flag2=1;
    int wall=0;
    for(int i=1; i<5; i++) {
        if (x0+i*dx>=0&&x0+i*dx<N&&y+i*dy>=0&&y0+i*dy<N) {
            if (m[x0+i*dx][y0+i*dy]==color) {
                if (flag1==1) {
                    side++;
                } else {
                    sides++;
                }
            } else if (m[x0+i*dx][y0+i*dy]==NONE) {
                if (flag1>0) {
                    if (m[x0+(i+1)*dx][y0+(i+1)*dy]==color) {
                        flag1--;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                wall++;
                break;
            }
        }
    }
    for(int i=1; i<5; i++) {
        if (x0-i*dx>=0&&x0-i*dx<N&&y0-i*dy>=0&&y0-i*dy<N) {
            if (m[x0-i*dx][y0-i*dy]==color) {
                if (flag2==1) {
                    oside++;
                } else {
                    osides++;
                }
            } else if (m[x0-i*dx][y0-i*dy]==NONE) {
                if (flag2>0) {
                    if (m[x0-(i+1)*dx][y0-(i+1)*dy]==color) {
                        flag2--;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                wall++;
                break;
            }
        }
    }
    if(side+oside>=4) {
        return LianWu;
    } else if (side+oside==3&&wall==0) {
        return HuoSi;
    } else if (side+oside==3&&wall==1) {
        return ChongSi;
    } else if (side+oside+sides+osides==3&&flag1+flag2==1) {
        return ChongSi;
    } else if (side+oside==2&&wall==0) {
        return HuoSan;
    } else if (side+oside+sides+osides==2&&flag1+flag2==1&&wall==0) {
        return HuoSan;
    } else if (side+oside==2&&wall==1) {
        return MianSan;
    } else if (side+oside+sides+osides==2&&flag1+flag2==1&&wall==1) {
        return MianSan;
    } else if (side+oside==1&&wall==0) {
        return HuoEr;
    } else if (side+oside==1&&wall==1) {
        return MianEr;
    } else if (side+oside==0&&wall==0) {
        return DanYi;
    } else {
        return Normal;
    }
}
point scanning(int level,int scan3x,int scan3y,int scan4x,int scan4y,int PorC,point list) {
    int tx3=scan3x,ty3=scan3y;
    int tx4=scan4x,ty4=scan4y;
    int max=-1000000000;
    int min=1000000000;
    point temp;
    if (level<FLOOR-1) {
        for (int x0=tx3; x0<=tx4; x0++) {
            for (int y0=ty3; y0<=ty4; y0++) {
                if (m[x0][y0]==NONE) {
                    if (x0==tx3&&x0-1>=0) {
                        scan3x--;
                    }
                    if (y0==ty3&&y0-1>=0) {
                        scan3y--;
                    }
                    if (x0==tx4&&x0+1<N) {
                        scan4x++;
                    }
                    if (y0==ty4&&y0+1<N) {
                        scan4y++;
                    }
                    m[x0][y0]=WorB;
                    list.todownx[level]=x0;
                    list.todowny[level]=y0;
                    WorB*=-1;
                    point tm;
                    tm=scanning(level+1,scan3x,scan3y,scan4x,scan4y,-1*PorC,list);
                    WorB*=-1;
                    m[x0][y0]=NONE;
                    scan3x=tx3;
                    scan3y=ty3;
                    scan4x=tx4;
                    scan4y=ty4;
                    if (tm.ifcut==1) {
                        continue;
                    } else if (PorC==PLAYER&&tm.score<mscore[level]||PorC==COMPUTER&&tm.score>mscore[level]) {
                        temp.ifcut==1;
                        return temp;
                    } else {
                        if (PorC==COMPUTER&&tm.score>max) {
                            max=tm.score;
                            temp=tm;
                        } else if (PorC==PLAYER&&tm.score<min) {
                            min=tm.score;
                            temp=tm;
                        }
                        if (PorC==COMPUTER&&max>mscore[level]) {
                            mscore[level]=max;
                        } else if(PorC==PLAYER&&min<mscore[level]) {
                            mscore[level]=min;
                        }
                    }
                }
            }
        }
        if (PorC==COMPUTER&&max>mscore[level]) {
            mscore[level]=max;
        } else if(PorC==PLAYER&&min<mscore[level]) {
            mscore[level]=min;
        }
        return temp;
    } else {
        for (int x0=tx3; x0<=tx4; x0++) {
            for (int y0=ty3; y0<=ty4; y0++) {
                if (m[x0][y0]==NONE) {
                    times++;
                    m[x0][y0]=WorB;
                    list.todownx[level]=x0;
                    list.todowny[level]=y0;
                    for (int k=tx3; k<=tx4; k++) {
                        for (int l=ty3; l<=ty4; l++) {
                        	if (m[k][l]!=NONE) {
                        		list.score+=pointjudge(k,l,PorC);
							}
                        }
                    }
                    m[x0][y0]=NONE;
                    if (PorC==PLAYER&&list.score<mscore[level]||PorC==COMPUTER&&list.score>mscore[level]) {
                        temp.ifcut=1;
                        return temp;
                    } else {
                        if (PorC==COMPUTER&&list.score>max) {
                            max=list.score;
                            temp=list;
                        } else if (PorC==PLAYER&&list.score<min) {
                            min=list.score;
                            temp=list;
                        }
                    }
                }
            }
        }
        if (PorC==COMPUTER&&max>mscore[level]) {
            mscore[level]=max;
        } else if(PorC==PLAYER&&min<mscore[level]) {
            mscore[level]=min;
        }
        return temp;
    }
}
