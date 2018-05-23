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
#define PLAYER

#define LianWu 1000
#define HuoSi 900
#define ChongSi 300
#define HuoSan 200
#define MianSan 100
#define Normal 50

#define floor 5

int n[N][N]= {0};
int m[N][N];
int WorB=BLACK;
int ComHd;
int PorC=COMPUTER;
int x,y;
int lastx,lasty;
int steps=0;
int scan1x=6;
int scan1y=6;
int scan2x=8;
int scan2y=8;
int todownx[floor];
int todowny[floor];
int todownmaxx[floor];
int todownmaxy[floor];
int maxscore=0;

void putbroad();
int winjudge();
int metajudge(int dx,int dy);
int down();
void cheki();
void cpybroad();
void ai();
int shapejudge(int,int);
int metajudge(int dx,int dy);
int pointjudge(int x0,int y0);
int metacount(int dx,int dy,int x0,int y0);
void scanning(int level,int score,int,int,int,int);

int main(int argc, char *argv[]) {
    printf("Select game mode\n");
    printf("'0' player vs player\n");
    printf("'1' player vs computer\n");
    if ('0'==getchar()) {
        getchar();
        system("cls");
        putbroad();
        while(!winjudge()&&!isDraw()) {
            scanf("%d%*c%d",&x,&y);
            getchar();
            down();
            cheki();
            system("cls");
            putbroad();
        }
    } else {
        getchar();
        system("cls");
        printf("'0' computer first\n");
        printf("'1' player first\n");
        if ('0'==getchar()) {
            ComHd=BLACK;
        } else {
            ComHd=WHITE;
        }
        getchar();
        system("cls");
        putbroad();
        while(!winjudge()&&!isDraw()) {
            if (ComHd==WorB) {
                ai();
            } else {
                scanf("%d%*c%d",&x,&y);
                getchar();
            }
            down();
            cheki();
            system("cls");
            putbroad();
        }
    }
    if (WorB==BLACK) {
        printf("BLACK is winner");
    } else {
        printf("WHITE is winner");
    }
    return TRUE;
}
void putbroad() {
    printf("   ");
    for (int i=0; i<N; i++) {
        printf("%2d",i);
    }
    printf("\n     ");
    printf("\n");
    for (int i=0; i<N; i++) {
        printf("%2d  ",i);
        for (int j=0; j<N; j++) {
            switch(n[j][i]) {
                case NONE: {
                        if (j==7&&i==7) {
                            printf("$ ");
                        } else if(i==14) {
                            printf("+ ");
                        } else {
                            printf("+ ");
                        }
                        break;
                    }
                case BLACK: {
                        printf("X ");
                        break;
                    }
                case WHITE: {
                        printf("O ");
                        break;
                    }
                default : {
                        break;
                    }
            }
        }
        printf("\n");
    }
    printf("\n\"-1,-1\"to undo\n");
    return;
}
int down() {
    if (x>=0&&y>=0&&x<N&&y<N&&n[x][y]==0) {
        n[x][y]=WorB;
        if (x<=scan1x&&x-1>=0) {
            scan1x=x-1;
        }
        if (y<=scan1y&&y-1>=0) {
            scan1y=y-1;
        }
        if (x>=scan2x&&x+1<N) {
            scan2x=x+1;
        }
        if (x>=scan2y&&y+1<N) {
            scan2y=y+1;
        }
		lastx=x;
        lasty=y;
		WorB=WorB*-1;
        steps++;
        return TRUE;
    }
    return FALSE;
}
int winjudge() {
    if(metajudge(1,0)) {
        return 1;
    } else if(metajudge(1,1)) {
        return 1;
    } else if(metajudge(0,1)) {
        return 1;
    } else if(metajudge(-1,1)) {
        return 1;
    } else {
        return 0;
    }
}
int metajudge(int dx,int dy) {
    int side=0,oside=0;
    //ÕýÏò¼ì²â
    for(int i=1; (x+i*dx>=0&&x+i*dx<N&&y+i*dy>=0&&y+i*dy<N)&&n[x+i*dx][y+i*dy]==WorB; i++) {
        side++;
    }
    for(int i=1; (x-i*dx>=0&&x-i*dx<N&&y-i*dy>=0&&y-i*dy<N)&&n[x-i*dx][y-i*dy]==WorB; i++) {
        oside++;
    }
    if(side+oside==4) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int isDraw() {
    if (steps==225-1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
void cheki() {
    if (x==-1&&y==-1) {
        n[lastx][lasty]=0;
        return;
    }
    return;
}
void cpybroad() {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            m[i][j]=n[i][j];
        }
    }
    return;
}
void ai() {
    cpybroad();
    scanning(0,0,scan1x,scan1y,scan2x,scan2y);
    WorB=ComHd;
    PorC=ComHd;
    x=todownmaxx[0];
    y=todownmaxy[0];
    cpybroad();
    maxscore=0;
}
int pointjudge(int x0,int y0) {
    return PorC*(metacount(1,0,x0,y0)+metacount(1,1,x0,y0)+metacount(0,1,x0,y0)+metacount(-1,1,x0,y0));
}
int metacount(int dx,int dy,int x0,int y0) {
    int side=0,oside=0;
    int flag=1;
    int wall=0;
    for(int i=1; i<5; i++) {
        if (x0+i*dx>=0&&x0+i*dx<N&&y+i*dy>=0&&y0+i*dy<N) {
            if (m[x0+i*dx][y0+i*dy]==WorB) {
                side++;
            } else if (m[x0+i*dx][y0+i*dy]==NONE) {
                if (flag>0) {
                    if (m[x0+(i+1)*dx][y0+(i+1)*dy]==WorB) {
                        flag--;
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
            if (m[x0-i*dx][y0-i*dy]==WorB) {
                oside++;
            } else if (m[x0-i*dx][y0-i*dy]==NONE) {
                if (flag>0) {
                    if (m[x0-(i+1)*dx][y0-(i+1)*dy]==WorB) {
                        flag--;
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
    if(side+oside==4&&flag==1) {
        return LianWu;
    } else if (side+oside==3&&flag==1&&wall==0) {
        return HuoSi;
    } else if (side+oside==3&&flag==1&&wall==1) {
        return ChongSi;
    } else if (side+oside==3&&flag==0) {
        return ChongSi;
    } else if (side+oside==2&&flag==1&&wall==0) {
        return HuoSan;
    } else if (side+oside==2&&flag==0) {
        return HuoSan;
    } else if (side+oside==2&&wall==0) {
        return MianSan;
    } else {
        return Normal;
    }
}
void scanning(int level,int score,int scan3x,int scan3y,int scan4x,int scan4y) {
	int tx3=scan3x,ty3=scan3y;
	int tx4=scan4x,ty4=scan4y;
    if (level<floor) {
        for (int x0=tx3; x0<=tx4; x0++) {
            for (int y0=ty3; y0<=ty4; y0++) {
                if (m[x0][y0]==NONE) {
                    score+=pointjudge(x0,y0);
                    m[x0][y0]=WorB;
                    if (scan3x>=x0&&x0-1>=0) {
                        scan3x=x0-1;
                    }
                    if (scan3y>=y0&&y0-1>=0) {
                        scan3y=y0-1;
                    }
                    if (scan4x<=x0&&x0+1<N) {
                        scan4x=x0+1;
                    }
                    if (scan4y<=y0&&y0+1<N) {
                        scan4y=y0+1;
                    }
                    todownx[level]=x0;
                    todowny[level]=y0;
                    WorB*=-1;
                    PorC*=-1;
                    scanning(level+1,score,scan3x,scan3y,scan4x,scan4y);
                    cpybroad();
                    scan3x=scan1x;
                    scan3y=scan1y;
                    scan4x=scan2x;
                    scan4y=scan2y;
                }
            }
        }
    } else {
        if (score>maxscore) {
            maxscore=score;
            for(int i=0; i<floor; i++) {
                todownmaxx[i]=todownx[i];
                todownmaxy[i]=todowny[i];
            }
        }
    }
    return;
}
