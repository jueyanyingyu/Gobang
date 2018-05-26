#include "Gamesupport.h"

int n[N][N];
int WorB;
int ComHd;
int PorC;
int x,y;
int lastx,lasty;
int steps;
int scan1x;
int scan1y;
int scan2x;
int scan2y;
int times;
int lastdownx[N*N];
int lastdowny[N*N];
clock_t start,stop;

int main(int argc, char *argv[]) {
    {
        times=0;
        n[N][N]=0;
        WorB=BLACK;
        PorC=COMPUTER;
        steps=0;
        scan1x=6;
        scan1y=6;
        scan2x=8;
        scan2y=8;
    }
    printf("Select game mode\n");
    printf("'0' player vs player\n");
    printf("'1' player vs computer\n");
    printf("'2' computer vs computer\n");
    int gamemode;
    scanf("%d",&gamemode);
    if (gamemode==0) {
        getchar();
        system("cls");
        putbroad();
        while(1!=winjudge()&&1!=isDraw()) {
            printf("\n\"-1,-1\"to undo\n");
            scanf("%d%*c%d",&x,&y);
            getchar();
            down();
            cheki();
            system("cls");
            putbroad();
            lastdownx[steps]=x;
            lastdowny[steps]=y;
            times=0;
        }
    } else if (gamemode==1) {
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
        while(1!=winjudge()&&1!=isDraw()) {
            if (ComHd==WorB) {
                printf("waiting...");
                start=clock();
                ai();
                stop=clock();
                WorB=ComHd;
                PorC=ComHd;
            } else {
                scanf("%d%*c%d",&x,&y);
                getchar();
            }
            down();
            system("cls");
            putbroad();
            lastdownx[steps]=x;
            lastdowny[steps]=y;
            times=0;
        }
    } else {
        while(1!=winjudge()&&1!=isDraw()) {
            start=clock();
            ai();
            stop=clock();
            down();
            system("cls");
            putbroad();
            lastdownx[steps]=x;
            lastdowny[steps]=y;
            times=0;
        }
    }
    WorB*=-1;
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
    printf("steps:%d\n",steps);
    printf("scaning times:%d\n",times);
    printf("time cost:%dms\n",stop-start);
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
        steps++;
        WorB=WorB*-1;
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
    WorB*=-1;
    for(int i=1; (x+i*dx>=0&&x+i*dx<N&&y+i*dy>=0&&y+i*dy<N)&&n[x+i*dx][y+i*dy]==WorB; i++) {
        side++;
    }
    for(int i=1; (x-i*dx>=0&&x-i*dx<N&&y-i*dy>=0&&y-i*dy<N)&&n[x-i*dx][y-i*dy]==WorB; i++) {
        oside++;
    }
    if(side+oside>=4) {
        WorB*=-1;
        return TRUE;
    } else {
        WorB*=-1;
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
        WorB*=-1;
        steps--;
        return;
    }
    return;
}

