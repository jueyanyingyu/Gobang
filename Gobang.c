#include "Gamesupport.h"

int n[N][N];			//棋盘数据
int x;
int y;				//欲下位置
int WorB;
int ComHd;
int PorC;
int lastx;
int lasty;
int steps;				//步骤
int scan1x;				//搜索范围
int scan1y;
int scan2x;
int scan2y;
int times;				//检索次数
int lastdownx[N*N];		//全局位置
int lastdowny[N*N];
int status[3][N][N][N*N];//白 空 黑 x y rand
int hash;
clock_t start;
clock_t stop;		//计时工具

point test;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    times=0;
    n[N][N]=0;
    steps=0;
    scan1x=6;
    scan1y=6;
    scan2x=8;
    scan2y=8;
    WorB=BLACK;
    for(int i=0; i<3; i++) {
        for(int j=0; j<N; j++) {
            for(int k=0; k<N; k++) {
                for(int l=0; l<N*N; l++) {
                    status[i][j][k][l]=rand()%8192;
                }
            }
        }
    }
    hash=0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            hash^=status[n[i][j]+1][i][j][i*j];
        }
    }					//初始化全局变量
    printf("Select game mode\n");
    printf("'0' player vs player\n");
    printf("'1' player vs computer\n");
    printf("'2' computer vs computer\n");
    int gamemode;		//选择游戏类型
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
                times=0;
                printf("waiting...");
                start=clock();
                ai(WorB);
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
        }
    } else {
        while(1!=winjudge()&&1!=isDraw()) {
            times=0;
            start=clock();
            ai(WorB);
            stop=clock();
            down();
            system("cls");
            putbroad();
            lastdownx[steps]=x;
            lastdowny[steps]=y;
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
    printf("   ");		//打印棋盘
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
    for(int i=0;i<FLOOR;i++) {
    	printf("%d %d\n",test.todownx[i],test.todowny[i]);
	}
    return;
}
int down() {			//改变棋盘数据
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
        lastx=x;		//反转颜色
        lasty=y;
        steps++;
        hash^=status[WorB+1][x][y][x*y];//更新hash值
        WorB=WorB*-1;
        return TRUE;
    }
    return FALSE;
}
int winjudge() {		//胜利判断
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
}						//单个方向胜利判断
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
int isDraw() {			//平局检测
    if (steps==225-1) {
        return TRUE;
    } else {
        return FALSE;
    }
}
void cheki() {			//悔棋
    if (x==-1&&y==-1) {
        n[lastx][lasty]=0;
        WorB*=-1;
        steps--;
        return;
    }
    return;
}

