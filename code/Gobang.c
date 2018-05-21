#include "Gamejudge.h"

int main(int argc, char *argv[]) {
    putbroad();
    WorB=WorB*-1;
    while(!winjudge()) {     
        down();
        cheki();
        system("cls");
        putbroad();
    }
    if (WorB==BLACK) {
        printf("BLACK is winner");
    } else {
        printf("WHITE is winner");
    }
    return FALSE;
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
                case 0: {
                        if (j==7&&i==7) {
                            printf("$ ");
                        } else if(i==14) {
                            printf("+ ");
                        } else {
                            printf("+ ");
                        }
                        break;
                    }
                case -1: {
                        printf("X ");
                        break;
                    }
                case 1: {
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
    scanf("%d,%d",&x,&y);
    char ch;
    while((ch=getchar())!='\n'&&ch!=EOF);
    if (x>=0&&y>=0&&x<N&&y<N&&n[x][y]==0) {
        n[x][y]=WorB;
        lastx=x;
        lasty=y;
        WorB=WorB*-1;
        return TRUE;
    }
    return FALSE;
}
int winjudge() {
    // 定义方向
    int dx,dy;
    //左右方向
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
    //正向检测
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
void cheki() {
    if (x==-1&&y==-1) {
        n[lastx][lasty]=0;
        return;
    }
    return;
}
